//
//  Fisheye.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 29/10/2016.
//
//

#include "Fisheye.hpp"
#include "EyeP/EyeP.hpp"
#include "EyeP/EyeP_g.hpp"
#include "EyeF/_EyeF.hpp"

#include "F135/F135.hpp"

namespace _Fisheye {
	int32_t (*map_k);
	int16_t (*map_w)[4];
}

void _zr(Fun1 fun1, int ln_x, int ln_y, int lp_x, int lp_y, float fov, float& z_x, float & z_y, float& r_x, float& r_y)
{
	z_x = (float)(ln_x + lp_x) / 2;
	z_y = (float)(ln_y + lp_y) / 2;
	r_x = fun1(fov) / (float)(lp_x - ln_x);
	r_y = r_x;
}

void _fl(FL& fl, int l_x, int l_y, float fov, float z_x, float z_y, float r_x, float r_y)
{
	fl.l_x = l_x;
	fl.l_y = l_y;
	fl.fov = fov;
	fl.z_x = z_x;
	fl.z_y = z_y;
	fl.r_x = r_x;
	fl.r_y = r_y;
}

bool Fisheye_camera(FD& fd, int l_x, int l_y, int ln_x, int ln_y, int lp_x, int lp_y, float fov)
{
	float z_x, z_y, r_x, r_y;
	_zr(fun1_af, ln_x, ln_y, lp_x, lp_y, fov, z_x, z_y, r_x, r_y);
	_fl(fd.camera, l_x, l_y, fov, z_x, z_y, r_x, r_y);

	return true;
}
bool Fisheye_display(FD& fd, int l_x, int l_y, float fov)
{
	float z_x, z_y, r_x, r_y;
	_zr(fun1_ag, 0, 0, l_x, l_y, fov, z_x, z_y, r_x, r_y);
	_fl(fd.display, l_x, l_y, fov, z_x, z_y, r_x, r_y);

	int k = 0;
//	fung_ag(-fov, -fov, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;
//	fung_ag(+fov, -fov, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;
//	fung_ag(+fov, +fov, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;
//	fung_ag(-fov, +fov, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;

	fung_ag(-fov, 0, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;
	fung_ag(0, -fov, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;
	fung_ag(+fov, 0, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;
	fung_ag(0, +fov, fd.cnr_o[k], fd.cnr_o[k + 1], nullptr); k += 2;

	int l = l_x*l_y;
	fd.map_k = new int32_t[l];
	fd.map_w = new int16_t[l][4];

	return true;
}

//void EyeP_per_pt(const float pt_f[], const float pt_g[], int pt_count, float u[])
void Fisheye_per(float pov_x, float pov_y, float per[8])
{
	per[0] = per[4] = 1;
	per[1] = per[3] = 0;
	float t_x, t_y;
	fung_ag(pov_x, pov_y, t_x, t_y, nullptr);
	per[2] = t_x;
	per[5] = t_y;
	per[6] = -t_x;
	per[7] = -t_y;
	per[6] = per[7] = 0;
}

bool Fisheye_setup(FD& fd, float pov_x, float pov_y)
{
	fd.pov_x = pov_x;
	fd.pov_y = pov_y;

	float fov = fd.display.fov;

	int k = 0;
//	fung_ag(pov_x - fov, pov_y - fov, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
//	fung_ag(pov_x + fov, pov_y - fov, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
//	fung_ag(pov_x + fov, pov_y + fov, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
//	fung_ag(pov_x - fov, pov_y + fov, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;

	fung_ag(pov_x - fov, pov_y - 0, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
	fung_ag(pov_x + 0, pov_y - fov, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
	fung_ag(pov_x + fov, pov_y + 0, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
	fung_ag(pov_x - 0, pov_y + fov, fd.cnr_p[k], fd.cnr_p[k + 1], nullptr); k += 2;
	
	float per[8];
//	EyeP_per_pt(fd.cnr_o, fd.cnr_p, 4, per);
	Fisheye_per(pov_x, pov_y, per);

	EyeP_kwmap_zr(fung_hf, per, fd.camera.l_x, fd.camera.l_y, fd.camera.z_x, fd.camera.z_y, fd.camera.r_x, fd.camera.r_y, fd.display.l_x, fd.display.l_y, fd.display.z_x, fd.display.z_y, fd.display.r_x, fd.display.r_y, fd.map_k, fd.map_w);

	return true;
}

bool Fisheye_run(FD& fd, uint8_t f[], uint8_t g[])
{
	EyeP_remap_w3(f, fd.camera.l_x, fd.camera.l_y, g, fd.display.l_x, fd.display.l_y, fd.map_k, fd.map_w);

	return true;
}

bool Fisheye_setup_135(FD& fd, float pov_x, float pov_y)
{
	Fisheye_camera(fd, f135::l_x, f135::l_y, 0, 0, f135::l_x, f135::l_y, f135::u);
	Fisheye_display(fd, f135::n_x, f135::n_y, f135::w);
	Fisheye_setup(fd, pov_x, pov_y);

	return true;
}

#if 0
bool Fisheye_fg(cv::Mat& f, cv::Mat& g, Fisheye& fisheye_f, Fisheye& fisheye_g)
{
	EyeF_map_fg(fisheye_f, fisheye_g, f.cols, f.rows, g.cols, g.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::map_k, f135::map_w);

	return true;
}

bool Fisheye_fh(cv::Mat& f, cv::Mat& h, Fisheye& fisheye_f, Fisheye& fisheye_h)
{
	EyeF_map_fh(fisheye_f, fisheye_h, f.cols, f.rows, h.cols, h.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, h.ptr(), h.cols, h.rows, f135::map_k, f135::map_w);

	return true;
}

bool Fisheye_fa(cv::Mat& f, cv::Mat& a, Fisheye& fisheye_f, Fisheye& fisheye_a)
{
	EyeF_map_fa(fisheye_f, fisheye_a, f.cols, f.rows, a.cols, a.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, a.ptr(), a.cols, a.rows, f135::map_k, f135::map_w);

	return true;
}

bool Fisheye_ag(cv::Mat& a, cv::Mat& g, Fisheye& fisheye_a, Fisheye& fisheye_g)
{
	EyeF_map_ag(fisheye_a, fisheye_g, a.cols, a.rows, g.cols, g.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(a.ptr(), a.cols, a.rows, g.ptr(), g.cols, g.rows, f135::map_k, f135::map_w);

	return true;
}

bool Fisheye_ah(cv::Mat& a, cv::Mat& h, Fisheye& fisheye_a, Fisheye& fisheye_h)
{
	EyeF_map_ah(fisheye_a, fisheye_h, a.cols, a.rows, h.cols, h.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(a.ptr(), a.cols, a.rows, h.ptr(), h.cols, h.rows, f135::map_k, f135::map_w);

	return true;
}

#endif
