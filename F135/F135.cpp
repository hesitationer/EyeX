// F135.cpp

#include "F135.hpp"
#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"

namespace f135 {
	int32_t h_map_k[n];
	int16_t h_map_w[n][4];
}

bool F135_fh(cv::Mat& f, float o, cv::Mat& g, float p)
{
	EyeF_map_fh(f.cols, f.rows, o, 0, g.cols, g.rows, p, 0, f135::h_map_k, f135::h_map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, f135::h_map_k, f135::h_map_w);

	return true;
}
