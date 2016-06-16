//
//  _EyeF.hpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef _EyeX_EyeF_hpp
#define _EyeX_EyeF_hpp

#include "EyeF.hpp"
#include "_EyeX.hpp"
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
void fung_gf(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_gf);
}

inline
void fung_af(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_af);
}

inline
void fung_ga(float f_x, float f_y, float& g_x, float& g_y, void*)
{
	_r(f_x, f_y, g_x, g_y, fun1_ga);
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

#endif
