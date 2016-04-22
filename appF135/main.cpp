//
//  main.cpp
//  appEyeF
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#include "F135/F135.hpp"
#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace cv;

int main(int argc, const char * argv[])
{
	int l_x = f135::l_x;
	int l_y = f135::l_y;
	int l = l_x*l_y;
	float o = f135::o;

	int m_x = f135::m_x;
	int m_y = f135::m_y;
	int m = m_x*m_y;
	float p = f135::p;

	int n_y = 576;
	float r_y = PI / 4;
	int n_x = n_y*2/3*2/3;
	int n = n_x*n_y;
	float hov = r_y * 2 / 3 * 2 / 3;
	float pov = hov;
	float w[] = { -pov*4/2, -pov*2/2, 0, +pov*2/2, +pov*4/2, };

	int32_t(*fg_map_k) = new int32_t[l];
	int16_t(*fg_map_w)[4] = new int16_t[l][4];

	int32_t(*fh_map_k) = new int32_t[n];
	int16_t(*fh_map_w)[4] = new int16_t[n][4];

	int32_t(*fp_map_k) = new int32_t[n];
	int16_t(*fp_map_w)[4] = new int16_t[n][4];

	int32_t(*fa_map_k) = new int32_t[l];
	int16_t(*fa_map_w)[4] = new int16_t[l][4];

	int32_t(*ah_map_k) = new int32_t[l];
	int16_t(*ah_map_w)[4] = new int16_t[l][4];

	//int32_t (*ah_map_k) = new int32_t[n];
	//int16_t (*ah_map_w)[4] = new int16_t[n][4];
	
	int32_t(*ap_map_k) = new int32_t[n];
	int16_t(*ap_map_w)[4] = new int16_t[n][4];

	int32_t(*hz_map_k) = new int32_t[m];
	int16_t(*hz_map_w)[4] = new int16_t[m][4];

	//char name[80] = { "vlcsnap-2014-10-08-14h10m44s169" };
	char name[80] = { "vlcsnap-2014-10-08-14h11m15s224" };
	//char name[80] = { "vlcsnap-2014-10-08-14h09m24s135" };
	char ext[8] = { ".png" };
	
	std::string fname("/Users/zhongsifen/Data/zhuxin/");
	
	Mat f = imread(fname + name + ".png", IMREAD_COLOR);
	imshow("input: f", f);
	waitKey(0);
	
	Mat g = Mat(Size(l_x, l_y), f.type());
	Mat a = Mat(Size(l_x, l_y), f.type());
	Mat b = Mat(Size(m_x, m_y), f.type());
	Mat z = Mat(Size(m_x, m_y*3/4), f.type());
	Mat h = Mat(Size(n_x, n_y), f.type());
	//Mat p = Mat(Size(n_x, n_y), f.type());

	std::string title("fisheye");

	EyeF_map_fh(f.cols, f.rows, o, 0, g.cols, g.rows, p, 0, fg_map_k, fg_map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, fg_map_k, fg_map_w);
	//EyeF_map_hz(g.cols, g.rows, fov, 0, z.cols, z.rows, fov, 0, hz_map_k, hz_map_w);
	//EyeP_remap_w3(g.ptr(), g.cols, g.rows, z.ptr(), z.cols, z.rows, hz_map_k, hz_map_w);

	EyeF_map_fa(f.cols, f.rows, o, 0, a.cols, a.rows, p, 0, fa_map_k, fa_map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, a.ptr(), a.cols, a.rows, fa_map_k, fa_map_w);
	EyeF_map_ah(a.cols, a.rows, p, 0, b.cols, b.rows, p, 0, ah_map_k, ah_map_w);
	EyeP_remap_w3(a.ptr(), a.cols, a.rows, b.ptr(), b.cols, b.rows, ah_map_k, ah_map_w);

	imshow("input: a", a);
	imshow("input: b", b);
	waitKey(0);

	return 0;

	for (int view=0; view<5; view++)
	{
		//EyeF_map_fp(f.cols, f.rows, fov, 0, p.cols, p.rows, pov, w[view], fp_map_k, fp_map_w);

		//EyeF_map_fh(f.cols, f.rows, fov, 0, h.cols, h.rows, hov, w[view], fh_map_k, fh_map_w);
		//EyeF_map_ah(a.cols, a.rows, aov, 0, n_x, n_y, hov, w[view], ah_map_k, ah_map_w);
		//EyeF_map_ap(a.cols, a.rows, aov, 0, n_x, n_y, pov, w[view], ap_map_k, ap_map_w);
		//EyeP_remap_w3(f.ptr(), f.cols, f.rows, a.ptr(), a.cols, a.rows, fa_map_k, fa_map_w);

		//EyeP_remap_w3(f.ptr(), f.cols, f.rows, p.ptr(), p.cols, p.rows, fp_map_k, fp_map_w);
		EyeP_remap_w3(a.ptr(), a.cols, a.rows, h.ptr(), h.cols, h.rows, ah_map_k, ah_map_w);
		//EyeP_remap_w3(a.ptr(), a.cols, a.rows, p.ptr(), p.cols, p.rows, ap_map_k, ap_map_w);

		imshow(title + (char)('0' + view), h);
		waitKey(0);
	}
//	for (int view=1; view<6; view++)
//	{
//		EyeF_map_pov(l1, l2, f_fov, f_pov, n_x, n_y, g_fov[view], g_pov[view], map_k, map_w);
//		EyeP_remap_w3(f.ptr(), f.cols, f.rows, h.ptr(), h.cols, h.rows, map_k, map_w);
//		imshow(title + char(view), h );
//		waitKey(0);
//		
////		imwrite(fname + "_pov_" + ('0' + view) + ".png", g);
//	}
	
	printf("Hello, world! This is gamma.\n");
	return 0;
}
