//
//  _EyeF.hpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef _EyeX_EyeF_hpp
#define _EyeX_EyeF_hpp

#include "EyeF.hpp"
#include "EyeX/_EyeX.hpp"
#include <math.h>
#include <float.h>

typedef float (*Fun1)(float);

inline
float fun1_aa(float a)
{
	return a;
}

inline
float fun1_af(float a)
{
	return tanf(a / 2) * 2;
}

inline
float fun1_fa(float f)
{
	return atanf(f / 2) * 2;
}

inline
float fun1_ag(float a)
{
	return tanf(a);
}

inline
float fun1_ga(float g)
{
	return atanf(g);
}

inline
float fun1_gf(float g)
{
	return (abs(g) < FLT_EPSILON) ? 0 : (-1 + sqrt(1 + g*g)) * 2 / g;
}

inline
float fun1_fg(float f)
{
	return (abs(f) > (2 - FLT_EPSILON)) ? FLT_MAX : f / (1 - f*f / 4);
}

inline
void _r(float f_x, float f_y, float& g_x, float& g_y, Fun1 fun1)
{
	float r = sqrt(f_x*f_x + f_y*f_y);
	if (r < FLT_EPSILON) { g_x = 0; g_y = 0; return; }
	float t = fun1(r) / r;
	g_x = f_x*t;
	g_y = f_y*t;
}

//EyeP.hpp
//typedef void(*FunG)(float f_x, float f_y, float& g_x, float& g_y, void* param);

inline
void fung_aa(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_aa);
}

inline
void fung_af(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_af);
}

inline
void fung_ag(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_ag);
}

inline
void fung_ga(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_ga);
}

inline
void fung_gf(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_gf);
}

inline
void fung_ha(float f_x, float f_y, float& g_x, float& g_y, void* param)
{
	float* w = (float*)param;
	float w_x = w[0];
	float w_y = w[1];

	_r(f_x, f_y, g_x, g_y, fun1_ga);
	g_x += w_x;
	g_y += w_y;
}

#include "EyeT/transform.hpp"
inline
void funx_per(float g_x_n, float g_x_p, float g_y_n, float g_y_p, float h_x_n, float h_x_p, float h_y_n, float h_y_p, void* param)
{
	float* per = (float*)param;

	cv::Point2f g[4], h[4];
	g[0] = cv::Point2f(g_x_n, g_y_n);
	g[1] = cv::Point2f(g_x_p, g_y_n);
	g[2] = cv::Point2f(g_x_n, g_y_p);
	g[3] = cv::Point2f(g_x_p, g_y_p);
	h[0] = cv::Point2f(h_x_n, h_y_n);
	h[1] = cv::Point2f(h_x_p, h_y_n);
	h[2] = cv::Point2f(h_x_n, h_y_p);
	h[3] = cv::Point2f(h_x_p, h_y_p);

	getPerTransform(g, h, per);
}

inline
void funx_per(float h_x_o, float h_x_n, float h_x_p, float g_x_o, float g_x_n, float g_x_p, void* param)
{
	float* per = (float*)param;

	float b = +g_x_o;
	float c = -g_x_o;
	float c_n = (h_x_n + b - g_x_n) / (h_x_n*g_x_n);
	float c_p = (h_x_p + b - g_x_p) / (h_x_p*g_x_p);

	per[0] = b;
	per[1] = c;
}

inline
void funx_per(float h_x_o, float h_y_o, float g_x_o, float g_y_o, void* param)
{
	float* per = (float*)param;

	float b_x = +g_x_o;
	float c_x = -g_x_o;
	float b_y = +g_y_o;
	float c_y = -g_y_o;

	per[0] = b_x;
	per[1] = c_x;
	per[2] = b_y;
	per[3] = c_y;
}

inline
void funx_bc(float g_n, float g_p, float h_n, float h_p, void* param)
{
	float* bc = (float*)param;
	float w = (g_p*h_p - g_n*h_n);
	if (fabs(w) < FLT_EPSILON) { bc[0] = 0; bc[1] = 0; return; }

	float c = ((g_p - g_n) - (h_p - h_n)) / w;
	float b = (c*g_n + 1)*h_n - g_n;
	bc[0] = b;
	bc[1] = c;
}

inline
void fung_hg(float h_x, float h_y, float& g_x, float& g_y, void* param)
{
#if 1
	float* u = (float*)param;

	float x = u[0] * h_x + u[1] * h_y + u[2];
	float y = u[3] * h_x + u[4] * h_y + u[5];
	float w = u[6] * h_x + u[7] * h_y + 1;

	g_x = x / w;
	g_y = y / w;
	//appPerTransform(h_x, h_y, g_x, g_y, param);
#else
	float* bc = (float*)param;
	float b_x = bc[0];
	float c_x = bc[1];
	float b_y = bc[2];
	float c_y = bc[3];
	float w = 1.0F/(c_x*h_x + c_y*h_y + 1);
	g_x = (h_x + b_x)*w;
	g_y = (h_y + b_y)*w;
#endif
}

inline
void fung_hf(
	float h_x, float h_y,
	float& f_x, float& f_y,
	void* param)
{
	float g_x, g_y;
	fung_hg(h_x, h_y, g_x, g_y, param);
	fung_gf(g_x, g_y, f_x, f_y, nullptr);
}

#endif
