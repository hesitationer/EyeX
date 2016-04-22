//
//  main.cpp
//  appEyeY
//
//  Created by SIFEN ZHONG on 30/8/15.
//
//

#include "EyeY/EyeY.hpp"

int _hist[256];

int main(int argc, const char * argv[]) {
	bool ret = false;
	int key = '\0';

	cv::Mat f, g, h, w;
	f = cv::imread(DATA_EYEX + "EyeY_1.png");
	cvtColor(f, g, cv::COLOR_BGR2GRAY);
	w = g.clone();
	cv::namedWindow("hole", 0);
	cv::resizeWindow("hole", 480, 480);
	cv::imshow("hole", w);
	key = cv::waitKey();

	EyeY_boundary(Hole->cen_x, Hole->cen_y, Hole->rad, Hole->boundary);
	EyeY_lap(g.data, g.cols, g.rows, Hole->boundary, w.data);
	cv::namedWindow("lap", 0);
	cv::resizeWindow("lap", 480, 480);
	cv::imshow("lap", w);
	key = cv::waitKey();

	return 0;
}
