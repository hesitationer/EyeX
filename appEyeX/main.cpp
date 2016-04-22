//
//  main.cpp
//  appEyeA
//
//  Created by SIFEN ZHONG on 30/8/15.
//
//

//#include "EyeA/EyeA.hpp"
//#include "EyeW/EyeW.hpp"

#include "EyeX/EyeX.hpp"
#include "Hole/Hole.hpp"

int main(int argc, const char * argv[]) {
	bool ret = false;
	int key = '\0';
	
	cv::Mat f, g, h, e, w;
	f = cv::imread(DATA_EYEX + "Hole_1.png");
	cvtColor(f, g, cv::COLOR_BGR2GRAY);
	h = g.clone();
	e = g.clone();
	w = g.clone();

	cv::namedWindow("hole", 0);
	cv::resizeWindow("hole", 480, 480);
	cv::imshow("hole", g);
	key = cv::waitKey();

	int* p = new int[hole::l_x*hole::l_y];
	float* r = new float[hole::l_x*hole::l_y];
	int count;
	hole_ring(hole::l_x, hole::l_y, hole::cen_x, hole::cen_y, hole::rad_o, hole::rad_i, p, r, count);
	hole_flatten(g.data, hole::l_x, hole::l_y, p, r, count, w.data, h.data, e.data);

	cv::namedWindow("flat", 0);
	cv::resizeWindow("flat", 480, 480);
	cv::imshow("flat", w);
	key = cv::waitKey();
	
	int hist[256];
	hole_hist(e.data, p, count, hist);

	//cv::threshold(g, h, 120, 200, 3);
	cv::imshow("hole", e);
	key = cv::waitKey();

	//EyeA u, v;
	//int s = 4;
	//EyeA_init(u, hole::l_x, hole::l_y, hole::cen_x, hole::cen_y, hole::rad_o, hole::rad_i);
 //	EyeA_s(u, s, v);
	//w.create(v.l_y, v.l_x, g.type());
	//EyeA_s(v, s, g.data, w.data);
	//cv::imshow("w", w);
	//key = cv::waitKey();
	//EyeA_h(v, w.data);
	//cv::imshow("w", w);
	//key = cv::waitKey();

	return 0;

	//EyeA_init_ar(v, -1, -1);
	//h.create(v.m_r, v.m_a, CV_8UC1);
	//EyeA_ar(v, w.data, h.data);

	//cv::imshow("ar", h);
	//key = cv::waitKey();


	//cv::Mat a, p, q;
	//h.convertTo(a, CV_32FC1);
	//p.create(a.size(), a.type());
	//q.create(a.size(), a.type());
	//float c, e;

	//EyeW_WV wv;
	//EyeW_wv_init(wv, a.cols, a.rows);
	//EyeW_wv_a(wv, (float*)a.data, (float*)p.data, (float*)q.data, c, e);
	//EyeW_wv_h(wv, (float*)a.data, (float*)p.data, c, (float*)q.data);
	//EyeW_wv_init(wv, h.cols, h.rows);
	//EyeW_wv_h(wv, h.data);

	//cv::Mat t;
	//t.create(cv::Size(v.m_a, v.m_r), CV_8UC1);
	//q.convertTo(t, CV_8UC1);
	cv::imshow("h", h);
	key = cv::waitKey();

	//EyeA_ring(v, h.data, w.data);
	//cv::imshow("w", w);
	//key = cv::waitKey();

	//cv::Mat show;
	//q.convertTo(show, CV_8UC1);
	//cv::imshow("show", show);
	//key = cv::waitKey();
	//cv::imwrite("q.png", show);

	return 0;
}
