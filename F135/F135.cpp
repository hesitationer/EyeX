// F135.cpp

#include "F135.hpp"
#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"

namespace f135 {
	Fov fov_f;
	Fov fov_g;
	Fov fov_a;

	int32_t map_k[l];
	int16_t map_w[l][4];

	int32_t map_i_k[l];
	int16_t map_i_w[l][4];

	int32_t map_o_k[l];
	int16_t map_o_w[l][4];
}
//EyeP_kwmap(fung_gf, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, n_x, n_y, n_x_n, n_x_p, n_y_n, n_y_p, map_k, map_w);

bool F135_init()
{
	fov_init(f135::fov_f, f135::u_x, f135::u_y, F);
	fov_init(f135::fov_g, f135::v_x, f135::v_y, G);

	return true;
}

bool F135_fg(cv::Mat& f, cv::Mat& g)
{
	EyeF_map_fg(f135::fov_f, f135::fov_g, f.cols, f.rows, g.cols, g.rows, f135::map_k, f135::map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::map_k, f135::map_w);

	return true;
}

bool F135_fa(cv::Mat& f, float o, cv::Mat& g, float p)
{
	EyeF_map_fa(f.cols, f.rows, o, 0, g.cols, g.rows, p, 0, f135::map_i_k, f135::map_i_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::map_i_k, f135::map_i_w);

	return true;
}

bool F135_ag(cv::Mat& f, float o, cv::Mat& g, float p)
{
	EyeF_map_ag(f.cols, f.rows, o, 0, g.cols, g.rows, p, 0, f135::map_o_k, f135::map_o_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::map_o_k, f135::map_o_w);

	return true;
}

bool F135_ah(cv::Mat& f, float o, cv::Mat& g, float q, float w)
{
	EyeF_map_ah(f.cols, f.rows, o, 0, g.cols, g.rows, q, w, f135::map_o_k, f135::map_o_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::map_o_k, f135::map_o_w);

	return true;
}
