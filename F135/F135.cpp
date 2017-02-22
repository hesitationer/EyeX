// F135.cpp

#include "F135.hpp"
#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"

namespace f135 {
	Fisheye fisheye_a;
	Fisheye fisheye_f;
	Fisheye fisheye_g;
	Fisheye fisheye_h[view_count][view_count];

	const int _l = 3840 * 2160;
	int32_t map_k[_l];
	int16_t map_w[_l][4];

	int32_t map_f_k[_l];
	int16_t map_f_w[_l][4];

	int32_t map_g_k[_l];
	int16_t map_g_w[_l][4];

	int32_t map_a_k[_l];
	int16_t map_a_w[_l][4];
}

bool F135_init()
{
	fisheye_init(f135::fisheye_a, f135::l_x, f135::l_y, f135::u, A);
	fisheye_init(f135::fisheye_f, f135::l_x, f135::l_y, f135::u, F);
	fisheye_init(f135::fisheye_g, f135::m_x, f135::m_y, f135::v, G);
	for (int i = 0; i < f135::view_count; i++) {
		for (int j = 0; j < f135::view_count; j++) {
			fisheye_init(f135::fisheye_h[i][j], f135::n_x, f135::n_y, f135::w, H, f135::view_x[i], f135::view_y[j]);
		}
	}
	return true;
}

bool F135_fg(cv::Mat& f, cv::Mat& g, Fisheye& fisheye_f, Fisheye& fisheye_g)
{
	EyeF_map_fg(fisheye_f, fisheye_g, f.cols, f.rows, g.cols, g.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::map_k, f135::map_w);

	return true;
}

bool F135_fh(cv::Mat& f, cv::Mat& h, Fisheye& fisheye_f, Fisheye& fisheye_h)
{
	EyeF_map_fh(fisheye_f, fisheye_h, f.cols, f.rows, h.cols, h.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, h.ptr(), h.cols, h.rows, f135::map_k, f135::map_w);

	return true;
}

bool F135_fa(cv::Mat& f, cv::Mat& a, Fisheye& fisheye_f, Fisheye& fisheye_a)
{
	EyeF_map_fa(fisheye_f, fisheye_a, f.cols, f.rows, a.cols, a.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, a.ptr(), a.cols, a.rows, f135::map_k, f135::map_w);

	return true;
}

bool F135_ag(cv::Mat& a, cv::Mat& g, Fisheye& fisheye_a, Fisheye& fisheye_g)
{
	EyeF_map_ag(fisheye_a, fisheye_g, a.cols, a.rows, g.cols, g.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(a.ptr(), a.cols, a.rows, g.ptr(), g.cols, g.rows, f135::map_k, f135::map_w);

	return true;
}

bool F135_ah(cv::Mat& a, cv::Mat& h, Fisheye& fisheye_a, Fisheye& fisheye_h)
{
	EyeF_map_ah(fisheye_a, fisheye_h, a.cols, a.rows, h.cols, h.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(a.ptr(), a.cols, a.rows, h.ptr(), h.cols, h.rows, f135::map_k, f135::map_w);

	return true;
}
