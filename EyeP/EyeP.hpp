//
//  EyeP.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 23/8/15.
//
//

#ifndef EyeX_EyeP_hpp
#define EyeX_EyeP_hpp

#include "EyeX.hpp"

typedef void(*FunG)(float f_x, float f_y, float& g_x, float& g_y, void* param);

void EyeP_kw(
	float t1, float t2,
	int& k1, int& k2,
	int16_t& w_0, int16_t& w_1, int16_t& w_2, int16_t& w_3)
	;
void EyeP_kwmap(
	FunG funG, void* param,
	int l_x, int l_y, float l_x_n, float l_x_p, float l_y_n, float l_y_p,
	int m_x, int m_y, float m_x_n, float m_x_p, float m_y_n, float m_y_p,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeP_kwmap(
	FunG funG, void* param,
	int l_x, int l_y, float l_x_n, float l_x_p, float l_y_n, float l_y_p,
	int m_x, int m_y, float m_x_n, float m_x_p, float m_y_n, float m_y_p,
	int32_t map_k[], int16_t map_w[][4],
	int32_t map_n[], int16_t map_z[][4])
	;
void EyeP_remap_w(
	uint8_t f[], int l1, int l2,
	uint8_t g[], int m1, int m2,
	int32_t map_k[], int16_t map_w[][4])
;
void EyeP_remap_w3(
	uint8_t f[], int l1, int l2,
	uint8_t g[], int m1, int m2,
	int32_t map_k[], int16_t map_w[][4])
;
void EyeP_remap_k(
	uint8_t f[], int l1, int l2,
	uint8_t g[], int m1, int m2,
	int32_t map_k[])
;
void EyeP_remap_yuv(
	uint8_t f_y[], uint8_t f_u[], uint8_t f_v[], int l1, int l2,
	uint8_t g_y[], uint8_t g_u[], uint8_t g_v[], int m1, int m2,
	int32_t map_k[], int16_t map_w[][4],
	int32_t map_n[], int16_t map_z[][4])
;

#endif
