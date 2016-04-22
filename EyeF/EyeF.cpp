//
//  EyeF.cpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#include "_EyeF.hpp"
#include "EyeP/EyeP.hpp"
#include <math.h>
#include <float.h>
#include "EyeF.hpp"

void EyeF_map_fh(
	int l_x, int l_y, float u, float o,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_0 = _af(o - u);
	float l_x_1 = _af(o + u);
	float n_x_0 = _ah(q - w);
	float n_x_1 = _ah(q + w);
	float r = (l_x_1 - l_x_0) / l_x;
	float t = (n_x_1 - n_x_0) / n_x;
	float l_y_0 = -r*l_y / 2;
	float l_y_1 = +r*l_y / 2;
	float n_y_0 = -t*n_y / 2;
	float n_y_1 = +t*n_y / 2;

	EyeP_kwmap(fung_hf, nullptr, l_x, l_y, l_x_0, l_x_1, l_y_0, l_y_1, n_x, n_y, n_x_0, n_x_1, n_y_0, n_y_1, map_k, map_w);
}

void EyeF_map_fa(
	int l_x, int l_y, float u, float o,
	int m_x, int m_y, float v, float p,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_0 = _af(o - u);
	float l_x_1 = _af(o + u);
	float m_x_0 = (p - v);
	float m_x_1 = (p + v);
	float r = (l_x_1 - l_x_0) / l_x;
	float s = (m_x_1 - m_x_0) / m_x;
	float l_y_0 = -r*l_y / 2;
	float l_y_1 = +r*l_y / 2;
	float m_y_0 = -s*m_y / 2;
	float m_y_1 = +s*m_y / 2;

	EyeP_kwmap(fung_af, nullptr, l_x, l_y, l_x_0, l_x_1, l_y_0, l_y_1, m_x, m_y, m_x_0, m_x_1, m_y_0, m_y_1, map_k, map_w);
}
void EyeF_map_ah(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float m_x_0 = (p - v);
	float m_x_1 = (p + v);
	float n_x_0 = _ah(q - w);
	float n_x_1 = _ah(q + w);
	float s = (m_x_1 - m_x_0) / m_x;
	float t = (n_x_1 - n_x_0) / n_x;
	float m_y_0 = -s*m_y / 2;
	float m_y_1 = +s*m_y / 2;
	float n_y_0 = -t*n_y / 2;
	float n_y_1 = +t*n_y / 2;

	EyeP_kwmap(fung_ha, nullptr, m_x, m_y, m_x_0, m_x_1, m_y_0, m_y_1, n_x, n_y, n_x_0, n_x_1, n_y_0, n_y_1, map_k, map_w);
}
void EyeF_map_ap(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float a[1] = { q, };
	float m_x_0 = (p - v);
	float m_x_1 = (p + v);
	float n_x_0 = _ah(0 - w);
	float n_x_1 = _ah(0 + w);
	float s = (m_x_1 - m_x_0) / m_x;
	float t = (n_x_1 - n_x_0) / n_x;
	float m_y_0 = -s*m_y / 2;
	float m_y_1 = +s*m_y / 2;
	float n_y_0 = -t*n_y / 2;
	float n_y_1 = +t*n_y / 2;

	EyeP_kwmap(fung_pa, a, m_x, m_y, m_x_0, m_x_1, m_y_0, m_y_1, n_x, n_y, n_x_0, n_x_1, n_y_0, n_y_1, map_k, map_w);
}

void EyeF_map_fp(
	int l_x, int l_y, float u, float o,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_0 = _af(o - u);
	float l_x_1 = _af(o + u);
	float n_x_0 = _ah(q - w);
	float n_x_1 = _ah(q + w);
	float d_x_0 = _ah(0 - w);
	float d_x_1 = _ah(0 + w);
	float bc[2];
	float r = (l_x_1 - l_x_0) / l_x;
	float t = (n_x_1 - n_x_0) / n_x;
	float l_y_0 = -r*l_y / 2;
	float l_y_1 = +r*l_y / 2;
	float n_y_0 = -t*n_y / 2;
	float n_y_1 = +t*n_y / 2;

	_hp(d_x_0, d_x_1, n_x_0, n_x_1, bc[0], bc[1]);
	EyeP_kwmap(fung_pf, bc, l_x, l_y, l_x_0, l_x_1, l_y_0, l_y_1, n_x, n_y, n_x_0, n_x_1, n_y_0, n_y_1, map_k, map_w);
}

void EyeF_map_zh(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float m_x_0 = _aa(p - v);
	float m_x_1 = _aa(p + v);
	float n_x_0 = _ah(q - w);
	float n_x_1 = _ah(q + w);
	float m_y_0 = m_x_0*m_y / m_x;
	float m_y_1 = m_x_1*m_y / m_x;
	float n_y_0 = n_x_0*n_y / n_x;
	float n_y_1 = n_x_1*n_y / n_y;

	EyeP_kwmap(fung_hz, nullptr, m_x, m_y, m_x_0, m_x_1, m_y_0, m_y_1, n_x, n_y, n_x_0, n_x_1, n_y_0, n_y_1, map_k, map_w);
}
void EyeF_map_hz(
	int n_x, int n_y, float w, float q,
	int m_x, int m_y, float v, float p,
	int32_t map_k[], int16_t map_w[][4])
{
	float m_x_0 = _aa(p - v);
	float m_x_1 = _aa(p + v);
	float n_x_0 = _ah(q - w);
	float n_x_1 = _ah(q + w);
	float m_y_0 = m_x_0*m_y / m_x;
	float m_y_1 = m_x_1*m_y / m_x;
	float n_y_0 = n_x_0*n_y / n_x;
	float n_y_1 = n_x_1*n_y / n_y;

	EyeP_kwmap(fung_zh, nullptr, n_x, n_y, n_x_0, n_x_1, n_y_0, n_y_1, m_x, m_y, m_x_0, m_x_1, m_y_0, m_y_1, map_k, map_w);
}
