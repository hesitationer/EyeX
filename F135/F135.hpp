// F135.hpp

#ifndef _F135_h_
#define _F135_h_

#include "EyeF/_EyeF.hpp"
#include "_opencv2.hpp"

const float _dr = PI / 180 / 2;

namespace f135 {
	const int l_x = 1280;
	const int l_y =  960;
	const int l = l_x*l_y;

	const int m_x = 1280;
	const int m_y =  720;
	const int m = m_x*m_y;

	const int n_x = 1136;
	const int n_y =  640;
	const int n = n_x*n_y;

	const float u = _dr * 135, u_x = u, u_y = u * l_y / l_x;
	const float v = _dr * 120, v_x = v, v_y = v * m_y / m_x;
	const float w = _dr * 120, w_x = w, w_y = w * n_y / n_x;
}

bool F135_init()
;
bool F135_fg(cv::Mat& f, cv::Mat& g)
;
bool F135_fa(cv::Mat& f, float o, cv::Mat& g, float p)
;
bool F135_ag(cv::Mat& f, float o, cv::Mat& g, float p)
;
bool F135_ah(cv::Mat& f, float o, cv::Mat& g, float q, float w);

#endif // !_F135_h_
