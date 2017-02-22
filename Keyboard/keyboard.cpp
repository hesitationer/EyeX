//
//  keyboard.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 1/10/2016.
//
//

#include "keyboard.hpp"
#include <cmath>

Point2f _point_f[4] = {
	Point2f( 434.33, 1116.13),
	Point2f(4152.62,  995.29),
	Point2f(4267.30, 2428.70),
	Point2f( 362.69, 2502.71),
};

float x_0 = _margin + 0.5F;
float y_0 = _margin + 0.5F;
float x_1 = _margin + _size.width  - 0.5F;
float y_1 = _margin + _size.height - 0.5F;

Point2f _point_g[4] = {
	Point2f(x_1, y_1),
	Point2f(x_0, y_1),
	Point2f(x_0, y_0),
	Point2f(x_1, y_0),
};

Point2f _point_box[4] = {
	Point2f( 270,  374),
	Point2f(3681,  373),
	Point2f( 240,  250),
	Point2f(3472, 1088),
};

Keyboard _keyboard = {
	_point_f,
	_point_g,
	_point_box,
};

const int m = (_size.width + _margin*2)*(_size.height + _margin*2 );
int32_t (*map_k) = new int32_t[m];
int16_t (*map_w)[4] = new int16_t[m][4];

bool keyboard_frame(Mat& f, Mat& g, Keyboard& keyboard)
{
	double* p = (double*)getPerspectiveTransform(keyboard.point_g, keyboard.point_f).data;
	Size s = Size((int)_size.width + _margin*2, (int)_size.height + _margin*2);
	g.create(s, f.type());
	float a[9];
	for (int i=0; i<9; i++) {
		a[i] = p[i];
	}

	EyeP_kwmap(EyeP_g, a, f.cols, f.rows, 0, f.cols, 0, f.rows, g.cols, g.rows, 0, g.cols, 0, g.rows, map_k, map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr() , g.cols, g.rows, map_k, map_w);
	
	return true;
}

bool keyboard_box(Mat& f, Mat& g, Keyboard& keyboard)
{
	Point2f* p = keyboard.point_box;
	Point2f p0 = p[0];
	Point2f p1 = p[1];
	Point2f lt = p[2];
	Point2f wh = p[3];
	
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	float l = sqrtf(dx*dx + dy*dy);
	float c = dx/l;
	float s = dy/l;
	float a[9];
	a[0] = c;
	a[1] = s;
	a[2] = lt.x;
	a[3] = -a[1];
	a[4] =  a[0];
	a[5] = lt.y;
	a[6] = 0;
	a[7] = 0;
	a[8] = 1;
	
	g.create(Size(wh.x, wh.y), f.type());
	EyeP_kwmap(EyeP_g, a, f.cols, f.rows, 0, f.cols, 0, f.rows, g.cols, g.rows, 0, g.cols, 0, g.rows, map_k, map_w);
	EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr() , g.cols, g.rows, map_k, map_w);
	
	return true;
}
