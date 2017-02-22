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
#include "EyeT/transform.hpp"

void fisheye_init(Fisheye& fisheye, int l_x, int l_y, float fov, AGF type, float pov_x, float pov_y)
{
	fisheye.l_x = l_x;
	fisheye.l_y = l_y;
	fisheye.fov = fov;
	fisheye.type = type;
	fisheye.pov_x = pov_x;
	fisheye.pov_y = pov_y;

	Fun1 fun1 = fun1_aa;
	Rov* rov = &fisheye.rov_a;
	rov->x_o = fun1(pov_x);
	rov->y_o = fun1(pov_y);
	rov->x_n = fun1(pov_x - fov);
	rov->x_p = fun1(pov_x + fov);
	rov->delta = (rov->x_p - rov->x_n) / l_x;
	rov->y_n = rov->y_o - rov->delta*l_y / 2;
	rov->y_p = rov->y_o + rov->delta*l_y / 2;

	fun1 = fun1_af;
	rov = &fisheye.rov_f;
	rov->x_o = fun1(pov_x);
	rov->y_o = fun1(pov_y);
	rov->x_n = fun1(pov_x - fov);
	rov->x_p = fun1(pov_x + fov);
	rov->delta = (rov->x_p - rov->x_n) / l_x;
	rov->y_n = rov->y_o - rov->delta*l_y / 2;
	rov->y_p = rov->y_o + rov->delta*l_y / 2;

	fun1 = fun1_ag;
	rov = &fisheye.rov_g;
	rov->x_o = fun1(pov_x);
	rov->y_o = fun1(pov_y);
	rov->x_n = fun1(pov_x - fov);
	rov->x_p = fun1(pov_x + fov);
	rov->delta = (rov->x_p - rov->x_n) / l_x;
	rov->y_n = rov->y_o - rov->delta*l_y / 2;
	rov->y_p = rov->y_o + rov->delta*l_y / 2;

	fun1 = fun1_ag;
	rov = &fisheye.rov_h;
	rov->x_o = 0;
	rov->y_o = 0;
	rov->x_n = -fun1(fov);
	rov->x_p = +fun1(fov);
	rov->delta = (rov->x_p - rov->x_n) / l_x;
	rov->y_n = rov->y_o - rov->delta*l_y / 2;
	rov->y_p = rov->y_o + rov->delta*l_y / 2;
}

void EyeF_map_fg(Fisheye& fov_f, Fisheye& fov_g,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_n = fov_f.rov_f.x_n, l_x_p = fov_f.rov_f.x_p, l_y_n = fov_f.rov_f.y_n, l_y_p = fov_f.rov_f.y_p;
	float m_x_n = fov_g.rov_g.x_n, m_x_p = fov_g.rov_g.x_p, m_y_n = fov_g.rov_g.y_n, m_y_p = fov_g.rov_g.y_p;
	EyeP_kwmap(fung_gf, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, m_x, m_y, m_x_n, m_x_p, m_y_n, m_y_p, map_k, map_w);
}

void EyeF_map_fh(Fisheye& fov_f, Fisheye& fov_h,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_o = fov_f.rov_f.x_o, l_y_o = fov_f.rov_f.y_o, l_x_n = fov_f.rov_f.x_n, l_x_p = fov_f.rov_f.x_p, l_y_n = fov_f.rov_f.y_n, l_y_p = fov_f.rov_f.y_p;
	float m_x_o = fov_h.rov_g.x_o, m_y_o = fov_h.rov_g.y_o, m_x_n = fov_h.rov_g.x_n, m_x_p = fov_h.rov_g.x_p, m_y_n = fov_h.rov_g.y_n, m_y_p = fov_h.rov_g.y_p;
	float n_x_o = fov_h.rov_h.x_o, n_y_o = fov_h.rov_h.y_o, n_x_n = fov_h.rov_h.x_n, n_x_p = fov_h.rov_h.x_p, n_y_n = fov_h.rov_h.y_n, n_y_p = fov_h.rov_h.y_p;
	float per[9];
	funx_per(n_x_o, n_y_o, m_x_o, m_y_o, per);
	EyeP_kwmap(fung_hf, per, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, m_x, m_y, n_x_n, n_x_p, n_y_n, n_y_p, map_k, map_w);
}

void EyeF_map_fa(Fisheye& fov_f, Fisheye& fov_a,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	float l_x_n = fov_f.rov_f.x_n, l_x_p = fov_f.rov_f.x_p, l_y_n = fov_f.rov_f.y_n, l_y_p = fov_f.rov_f.y_p;
	float m_x_n = fov_a.rov_a.x_n, m_x_p = fov_a.rov_a.x_p, m_y_n = fov_a.rov_a.y_n, m_y_p = fov_a.rov_a.y_p;
	EyeP_kwmap(fung_af, nullptr, l_x, l_y, l_x_n, l_x_p, l_y_n, l_y_p, m_x, m_y, m_x_n, m_x_p, m_y_n, m_y_p, map_k, map_w);
}

void EyeF_map_ag(Fisheye& fov_a, Fisheye& fov_g,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
{
	EyeP_kwmap(fung_ga, nullptr,
		l_x, l_y, fov_a.rov_a.x_n, fov_a.rov_a.x_p, fov_a.rov_a.y_n, fov_a.rov_a.y_p,
		m_x, m_y, fov_g.rov_g.x_n, fov_g.rov_g.x_p, fov_g.rov_g.y_n, fov_g.rov_g.y_p,
		map_k, map_w);
}

void EyeF_map_ah(Fisheye& fov_a, Fisheye& fov_h,
	int l_x, int l_y, int n_x, int n_y,
	int32_t map_k[], int16_t map_w[][4])
{
	float* param = new float[2];
	param[0] = fov_h.pov_x;
	param[1] = fov_h.pov_y;
	EyeP_kwmap(fung_ha, param,
		l_x, l_y, fov_a.rov_a.x_n, fov_a.rov_a.x_p, fov_a.rov_a.y_n, fov_a.rov_a.y_p,
		n_x, n_y, fov_h.rov_h.x_n, fov_h.rov_h.x_p, fov_h.rov_h.y_n, fov_h.rov_h.y_p,
		map_k, map_w);
}
