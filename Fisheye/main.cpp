//
//  main.cpp
//  appFisheye
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#include "Fisheye/Fisheye.hpp"
#include "EyeX/EyeX.hpp"
#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"
#include <stdint.h>
#include <string>
#include <math.h>
#include <iostream>
#include "_opencv2.hpp"
using namespace cv;

int main(int argc, const char * argv[])
{
	std::string path("/Users/zhongsifen/Data/fisheye/");
	char name[80] = { "1600x1476" };
	char ext[8] = { ".jpg" };

	Mat f = imread(path + name + ext, IMREAD_COLOR);

	const int e = 0;
	const int ln_x = 96 + e;
	const int lp_x = 1488 - e;
	const int ln_y = 56 + e;
	const int lp_y = 1448 - e;
	const float fov_c = DR(180);

	const int m_x = 640;
	const int m_y = 640;
	const float fov_d = fov_c / 3;
	float pov_x = 0;
	float pov_y = 0;
	//	Rect roi(Point(412, 24), Point(3196, 2808));
	Rect roi(Point(ln_x, ln_y), Point(lp_x, lp_y));
	Mat f_180;
	f(roi).copyTo(f_180);

	Mat show;
	resize(f_180, show, Size(640, 640));

	imshow("Fisheye:f", show);
	waitKey();

	FD fd;
	Fisheye_camera(fd, f.cols, f.rows, roi.tl().x, roi.tl().y, roi.br().x, roi.br().y, fov_c);
	Fisheye_display(fd, m_x, m_y, DR(150));
	Fisheye_setup(fd, 0, 0);
	Mat h(Size(fd.display.l_x, fd.display.l_y), f.type());
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h 0", h);	waitKey();

	int fourcc_mjpg = CV_FOURCC('M', 'J', 'P', 'G');
	int fourcc_h264 = CV_FOURCC('H', '2', '6', '4');
	VideoWriter wri(path + name + "_p.avi", fourcc_mjpg, 25, h.size());			if (!wri.isOpened()) return -1;

	Fisheye_display(fd, m_x, m_y, fov_d);

	const float t = fov_d * 2;
	const float u = fov_c - t;
	const float s = DR(1);
	const float r = fov_c - fov_d;
	const float z = fov_d;

	float v = 0;
	Fisheye_setup(fd, v, 0);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h 0", h);	waitKey();

	v = +r;
	Fisheye_setup(fd, v, 0);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h +r", h);	waitKey();

	v = -r;
	Fisheye_setup(fd, v, 0);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h -r", h);	waitKey();

	v = +r;
	Fisheye_setup(fd, 0, v);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h +r", h);	waitKey();

	v = -r;
	Fisheye_setup(fd, 0, v);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h -r", h);	waitKey();

	Fisheye_setup(fd, -r, -r);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h -r", h);	waitKey();

	Fisheye_setup(fd, +r, -r);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h -r", h);	waitKey();

	Fisheye_setup(fd, +r, +r);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h -r", h);	waitKey();

	Fisheye_setup(fd, -r, +r);
	Fisheye_run(fd, f.data, h.data);
	imshow("Fisheye:h -r", h);	waitKey();

	return 0;

	while (v<+r) {
		Fisheye_setup(fd, v, 0);
		Fisheye_run(fd, f.data, h.data);
		wri.write(h);
		v += s;
		imshow("Fisheye:h", h);
		waitKey(1);
	}
	while (v>-r) {
		Fisheye_setup(fd, v, -z);
		Fisheye_run(fd, f.data, h.data);
		wri.write(h);
		v -= s;
		imshow("Fisheye:h", h);
		waitKey(1);
	}
	while (v<+r) {
		Fisheye_setup(fd, v, +z);
		Fisheye_run(fd, f.data, h.data);
		wri.write(h);
		v += s;
		imshow("Fisheye:h", h);
		waitKey(1);
	}
	while (v>-r) {
		Fisheye_setup(fd, v, 0);
		Fisheye_run(fd, f.data, h.data);
		wri.write(h);
		v -= s;
		imshow("Fisheye:h", h);
		waitKey(1);
	}

#if 0
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
#endif

	
	printf("Hello, world! This is F135.\n");	waitKey(0);
	return 0;
}
