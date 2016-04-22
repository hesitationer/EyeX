#pragma once

#include "EyeX/EyeX.hpp"
#include "../_opencv2.hpp"

namespace f135 {
	// parameters of YUV frames from capture
	const int l_x = 1280;
	const int l_y =  960;
	const int l = l_x*l_y;
	const float o = 135.0F * PI2 / 360 / 2;

	const int m_x = 1280;
	const int m_y =  720;
	const int m = m_x*m_y;
	const float p = 120.0F * PI2 / 360 / 2;

	const int n_x = 1136;
	const int n_y =  640;
	const int n = n_x*n_y;
	const float q = 120.0F * PI2 / 360 / 2;
}
