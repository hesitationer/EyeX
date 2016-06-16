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

void afg(float a, float& f, float& g)
{
	f = fun1_af(a);
	g = fun1_ag(a);
}

void fov_init(Fov& fov, float fov_x, float fov_y, AGF type, float v_x, float v_y)
{
	fov.fov_x = fov_x;
	fov.fov_y = fov_y;
	fov.type = type;
	fov.v_x = v_x;
	fov.v_y = v_y;
	Fun1 fun1 = fun1_aa;
	switch (type) {
	case A: fun1 = fun1_aa; break;
	case F: fun1 = fun1_af; break;
	case G: fun1 = fun1_ag; break;
	default: assert(false); break;
	}
	float x = fun1(fov_x);
	float y = fun1(fov_y);
	fov.x_n = -x;
	fov.x_p = +x;
	fov.y_n = -y;
	fov.y_p = +y;
}

void EyeF_map_fg(Fov& fov_f, Fov& fov_g,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_n = fov_f.x_n, l_x_p = fov_f.x_p, l_y_n = fov_f.y_n, l_y_p = fov_f.y_p;
	float m_x_n = fov_g.x_n, m_x_p = fov_g.x_p, m_y_n = fov_g.y_n, m_y_p = fov_g.y_p;
	EyeP_kwmap(fung_gf, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, m_x, m_y, m_x_n, m_x_p, m_y_n, m_y_p, map_k, map_w);
}

void EyeF_map_fg(
	int l_x, int l_y, float l_x_n, float l_x_p, float l_y_n, float l_y_p,
	int n_x, int n_y, float n_x_n, float n_x_p, float n_y_n, float n_y_p,
	int32_t map_k[], int16_t map_w[][4])
{
	EyeP_kwmap(fung_gf, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, n_x, n_y, n_x_n, n_x_p, n_y_n, n_y_p, map_k, map_w);
}

void EyeF_map_fg(
	int l_x, int l_y, float u, float o,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_n = fun1_af(o - u);
	float l_x_p = fun1_af(o + u);
	float n_x_n = fun1_ag(q - w);
	float n_x_p = fun1_ag(q + w);
	float l_y_n = (l_x_n - l_x_p)*l_y / l_x / 2;
	float l_y_p = -l_y_n;
	float n_y_0 = (n_x_n - n_x_p)*n_y / n_x / 2;
	float n_y_1 = -n_y_0;

	EyeP_kwmap(fung_gf, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, n_x, n_y, n_x_n, n_x_p, n_y_0, n_y_1, map_k, map_w);
}

void EyeF_map_fa(
	int l_x, int l_y, float u, float o,
	int m_x, int m_y, float v, float p,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_n = fun1_af(o - u);
	float l_x_p = fun1_af(o + u);
	float m_x_n = fun1_aa(p - v);
	float m_x_p = fun1_aa(p + v);
	float r = (l_x_p - l_x_n) / l_x;
	float s = (m_x_p - m_x_n) / m_x;
	float l_y_n = -r*l_y / 2;
	float l_y_p = +r*l_y / 2;
	float m_y_n = -s*m_y / 2;
	float m_y_p = +s*m_y / 2;

	EyeP_kwmap(fung_af, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, m_x, m_y, m_x_n, m_x_p, m_y_n, m_y_p, map_k, map_w);
}

void EyeF_map_ag(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float m_x_n = fun1_aa(p - v);
	float m_x_p = fun1_aa(p + v);
	float n_x_n = fun1_ag(q - w);
	float n_x_p = fun1_ag(q + w);
	float s = (m_x_p - m_x_n) / m_x;
	float t = (n_x_p - n_x_n) / n_x;
	float m_y_n = -s*m_y / 2;
	float m_y_p = +s*m_y / 2;
	float n_y_0 = -t*n_y / 2;
	float n_y_1 = +t*n_y / 2;

	EyeP_kwmap(fung_ga, nullptr, m_x, m_y, m_x_n, m_x_p, m_y_n, m_y_p, n_x, n_y, n_x_n, n_x_p, n_y_0, n_y_1, map_k, map_w);
}

void EyeF_map_ah(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
{
	float m_x_n = fun1_aa(p - v);
	float m_x_p = fun1_aa(p + v);
	float n_x_n = fun1_ag(q - w);
	float n_x_p = fun1_ag(q + w);
	float s = (m_x_p - m_x_n) / m_x;
	float t = (n_x_p - n_x_n) / n_x;
	float m_y_n = -s*m_y / 2;
	float m_y_p = +s*m_y / 2;
	float n_y_0 = -t*n_y / 2;
	float n_y_1 = +t*n_y / 2;

	float* param = new float[2];
	param[0] = q;
	param[1] = 0;
	EyeP_kwmap(fung_ha, param, m_x, m_y, m_x_n, m_x_p, m_y_n, m_y_p, n_x, n_y, n_x_n, n_x_p, n_y_0, n_y_1, map_k, map_w);
}
