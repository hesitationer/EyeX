//
//  _EyeF.hpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef _EyeX_EyeP_hpp
#define _EyeX_EyeP_hpp

#include "EyeX/_EyeX.hpp"
#include <math.h>
#include <float.h>

inline
float _aa(float a)
{
	return a;
}

inline
float _af(float a)
{
	return tanf(a / 2.0F)*2.0F;
}

inline
float _fa(float f)
{
	return atanf(f/2.0F)*2.0F;
}

inline
float _ah(float a)
{
	return tanf(a);
}

inline
float _ha(float h)
{
	return atanf(h);
}

inline
float _fh(float f)
{
	return f / (1 - f*f / 4);
}

inline
float _hf(float h)
{
	return (-1 + sqrt(1 + h*h)) * 2 / h;
}

inline
void fung_af(
	float f_x, float f_y,
	float& g_x, float& g_y,
	void* param)
{
	float rr = (f_x*f_x + f_y*f_y);
	if (rr < FLT_EPSILON) { g_x = 0; g_y = 0; return; }
	float r = sqrtf(rr);
	float t = _af(r) / r;
	g_x = f_x*t;
	g_y = f_y*t;
}

inline
void fung_ha(
	float f_x, float f_y,
	float& g_x, float& g_y,
	void* param)
{
	float rr = (f_x*f_x + f_y*f_y);
	if (rr < FLT_EPSILON) { g_x = 0; g_y = 0; return; }
	float r = sqrtf(rr);
	float t = _ha(r) / r;
	g_x = f_x*t;
	g_y = f_y*t;
}

inline
void fung_pa(
	float f_x, float f_y,
	float& g_x, float& g_y,
	void* param)
{
	float a = *((float *)param);
	float rr = (f_x*f_x + f_y*f_y);
	if (rr < FLT_EPSILON) { g_x = 0; g_y = 0; return; }
	float r = sqrtf(rr);
	float t = _ha(r) / r;
	g_x = f_x*t + a;
	g_y = f_y*t;
}

inline
void fung_fh(
	float f_x, float f_y,
	float& h_x, float& h_y,
	void* param)
{
	float rr = (f_x*f_x + f_y*f_y);
	if (rr < FLT_EPSILON) { h_x = 0; h_y = 0; return; }
	float t = 1 / (1 - rr / 4);
	h_x = f_x*t;
	h_y = f_y*t;
}

inline
void fung_hf(
	float h_x, float h_y,
	float& f_x, float& f_y,
	void* param)
{
	//f_x = _hf(h_x);
	//f_y = _hf(h_y);
	float rr = (h_x*h_x + h_y*h_y);
	if (rr < FLT_EPSILON) { f_x = 0; f_y = 0; return; }
	float r = sqrt(rr);
	float t = _hf(r)/r;
	//float t = (-1 + sqrt(1 + rr)) * 2 / rr;
	f_x = h_x*t;
	f_y = h_y*t;
}

inline
void _hp(
	float h_0, float h_1, float p_0, float p_1,
	float& b,  float& c)
{
	float w = (h_1*p_1 - h_0*p_0);
	if (fabs(w) < FLT_EPSILON) { b = 0; c = 0; return; }

	c = ((h_1 - h_0) - (p_1 - p_0))/w;
	b = (c*h_0 + 1)*p_0 - h_0;
}

inline
void _ph(
	float p_x, float p_y, float b, float c,
	float& h_x, float& h_y)
{
	float w = 1.0F/(c*p_x + 1);
	h_x = (p_x + b)*w;
	h_y = p_y*w;
}

inline
void fung_pf(
	float p_x, float p_y,
	float& f_x, float& f_y,
	void* param)
{
	float* bc = (float*)param;
	float h_x, h_y;
	_ph(p_x, p_y, bc[0], bc[1], h_x, h_y);
	float rr = (h_x*h_x + h_y*h_y);
	if (rr < FLT_EPSILON) { f_x = 0; f_y = 0; return; }
	float t = (-1 + sqrt(1 + rr)) * 2 / rr;
	f_x = h_x*t;
	f_y = h_y*t;
}

inline
void fung_zh(
	float z_a, float z_y,
	float& h_x, float& h_y,
	void* param)
{
	h_x = tanf(z_a);
	h_y = z_y * sqrt(h_x*h_x + 1);
}
inline
void fung_hz(
	float h_x, float h_y,
	float& z_a, float& z_y,
	void* param)
{
	z_a = atanf(h_x);
	z_y = h_y / sqrt(h_x*h_x + 1);
}
inline
void fung_zf(
	float z_a, float z_y,
	float& f_x, float& f_y,
	void* param)
{

}
#endif
