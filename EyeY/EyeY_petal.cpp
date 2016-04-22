//
//  EyeY_petal.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 28/11/15.
//
//

#include "EyeY_petal.hpp"
#include "EyeY.hpp"
#include "EyeP/EyeP.hpp"

float _m = 240;
float _l = _m * (1.0 - 1.0/16);
float _n = _m * (1.0 + 1.0/16);

bool EyeY_Petal(cv::Mat& f)
{
	cv::Mat g, h;
	std::vector<std::vector<cv::Point>> contours;
	cv::cvtColor(f, g, cv::COLOR_BGR2GRAY);
	cv::blur(g, g, cv::Size(3,3));
	cv::threshold(g, g, 240, 64, cv::THRESH_BINARY_INV);
	cv::imshow("EyeY", g);
	cv::waitKey();
	cv::Canny(g, h, _l, _n, 3);
	cv::imshow("EyeY", h);
	cv::waitKey();
	cv::findContours(h, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
	int k = 0;
	size_t size = contours[k].size();
	for(int i = 1; i<(int)contours.size(); i++) {
		if (contours[i].size() > size) {
			k = i;
			size = contours[k].size();
		}
	}
	cv::drawContours(f, contours, k, cv::Scalar(0xFF, 0x00, 0x00));
	
	std::vector<cv::Point> contour = contours[k];
	cv::Moments mu = cv::moments(contour, true);
	//	cv::Moments mu = cv::moments(g, true);
	float area = mu.m00;
	float cen1 = mu.m10/area;
	float cen2 = mu.m01/area;
	float rad = sqrtf(area/PI);
	std::cout << area << "  " << rad << "   " << cen1 << "  " << cen2 << "\n";
	cv::circle(f, cv::Point2f(cen1, cen2), 2, cv::Scalar(0x00, 0x00, 0xFF));
	cv::imshow("EyeY", f);
	cv::waitKey();
	
	int l1 = f.cols;
	int l2 = f.rows;
	int mr =  144 ;
	int ma =  720;
	int m = mr*ma;
	int32_t (*map_k) = new int32_t[m];
	int16_t (*map_w)[4] = new int16_t[m][4];
	
	EyeY_map(l1, l2, cen1, cen2, rad, ma, mr, 0.5F, 1.125F, map_k, map_w);
	
	cv::Mat w = cv::Mat(cv::Size(ma, mr), f.type());
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, w.ptr(), w.cols, w.rows, map_k, map_w);
	cv::imshow("EyeY", w);
	cv::waitKey();
	
	cv::Mat z = cv::Mat(cv::Size(ma, mr), g.type());
	EyeP_remap_w(g.ptr(), g.cols, g.rows, z.ptr(), z.cols, z.rows, map_k, map_w);
	cv::imshow("EyeY", z);
	cv::waitKey();
	
	cv::imwrite(DATA_EYEX + "EyeY_z.pgm", z);
	
	//	cv::Rect roi(cv::Point(150, 0), cv::Size(36, 144));
	//	cv::Mat p = z(roi);
	//	cv::Moments mt;
	//	EyeY_Moment(p, mt);
	//
	//	float m10 = mt.m10/mt.m00;
	//	float m01 = mt.m01/mt.m00;
	//
	//	std::cout << m10 << "  " << m01 << "\n";
	
	float t, e;
	EyeY_A(z.ptr(), ma, mr, 10, t);
	e = t*360/PI2;
	
	std::cout << t << "  " << e << "\n";
	
	return true;
}
