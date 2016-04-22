//
//  main.cpp
//  appEyeJ
//
//  Created by SIFEN ZHONG on 22/10/15.
//
//

#include "EyeX.hpp"
#include "EyeT.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
	cv::Mat f = cv::imread(DATA_EYEX + "jdb/003.png");
	cv::Mat h = f.clone();
	cv::imshow("EyeJ:f", f);
	cv::waitKey();
	
	cv::Point2f pt_src[4] = {
		cv::Point2f(257.0, 140.0),	cv::Point2f(418.0, 128.0),
		cv::Point2f(289.0, 306.0),	cv::Point2f(423.0, 294.0),
	};
	cv::Point2f pt_dst[4] = {
		cv::Point2f(256.0, 140.0),	cv::Point2f(416.0, 140.0),
		cv::Point2f(256.0, 340.0),	cv::Point2f(416.0, 340.0),
	};
	
	EyeT eyet;
	eyet.setType(EyeT::TRANSFORM_PER);
	cv::Mat op = eyet.getTransform(pt_src, pt_dst, 4);
	eyet.appTransform(f, h, op);
	cv::imshow("EyeJ:h", h );
	cv::waitKey();
	
	std::cout << "Hello, World!\n";
    return 0;
}
