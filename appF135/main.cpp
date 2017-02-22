//
//  main.cpp
//  appF135
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
	std::string path("/Users/zhongsifen/Data/fisheye/");
	char name[80] = { "chart_135" };
	char ext[8] = { ".png" };
	std::string title("fisheye");
	
	Mat f = imread(path + name + ".png", IMREAD_COLOR);
//	namedWindow(title, WINDOW_NORMAL);
//	resizeWindow(title, 640, 480);
//	imshow(title, f);
	imshow("F135:f", f);
	waitKey();
	
	const int datatype = f.type();
	Mat a  = Mat(Size(f135::l_x, f135::l_y), datatype);
	
	Mat ag = Mat(Size(f135::n_x, f135::n_y), datatype);
	Mat ah = Mat(Size(f135::n_x, f135::n_y), datatype);
	Mat fg = Mat(Size(f135::n_x, f135::n_y), datatype);
	Mat fh = Mat(Size(f135::n_x, f135::n_y), datatype);
	
	F135_init();
	F135_fa(f, a);
	imshow("F135:a", a);
	waitKey();

	Fisheye _f = f135::fisheye_f;
	const float fov = _f.fov;
	const int m_x = 2400;
	const int m_y = 1350;
	Mat g = Mat(Size(m_x, m_y), datatype);
	Fisheye _g;
	fisheye_init(_g, m_x, m_y, fov, G);
	F135_fg(f, g, _f, _g);
	imwrite(path + name + "_g.png", g);
	imshow("F135:g", g);
	waitKey();
	
//	return 0;
	
	Fisheye _h;
	const int n_x= 640;
	const int n_y= 640;
	const float w=_dr*60;
	const float r= fov - w;
	const float s=_dr*1 ;
	const float z=_dr*75;
 	Mat h = Mat(Size(n_x, n_y), datatype);
	int fourcc_mjpg = CV_FOURCC('M', 'J', 'P', 'G');
	int fourcc_h264 = CV_FOURCC('H', '2', '6', '4');
	VideoWriter wri(path + name + "_p.avi", fourcc_mjpg, 25, h.size());			if (!wri.isOpened()) return -1;
	
	float v=-r;
	while (v<+r) {
		fisheye_init(_h, n_x, n_y, w, H, v, 0);
		F135_fh(f, h, _f, _h);
		wri.write(h);
		v+=s;
		imshow("F135: h", h);
		waitKey(5);
	}
	while (v>-r) {
		fisheye_init(_h, n_x, n_y, w, H, v, -z);
		F135_fh(f, h, _f, _h);
		wri.write(h);
		v-=s;
		imshow("F135: h", h);
		waitKey(5);
	}
	while (v<+r) {
		fisheye_init(_h, n_x, n_y, w, H, v, +z);
		F135_fh(f, h, _f, _h);
		wri.write(h);
		v+=s;
		imshow("F135: h", h);
		waitKey(5);
	}
	while (v>-r) {
		fisheye_init(_h, n_x, n_y, w, H, v, 0);
		F135_fh(f, h, _f, _h);
		wri.write(h);
		v-=s;
		imshow("F135: h", h);
		waitKey(5);
	}
	
//	F135_ah(a, ah, f135::fisheye_a, f135::fisheye_h[f135::view_zero+2][f135::view_zero]);
//	imshow("F135: ah", ah);
//	
//	F135_ag(a, g, f135::fisheye_a, f135::fisheye_g);
//	imshow("F135: ag", g);
//	
//	F135_fg(f, g, f135::fisheye_f, f135::fisheye_g);
//	imshow("F135: fg", g);

	wri.release();
	
	waitKey(0);
	
	printf("Hello, world! This is F135.\n");
	return 0;
}
