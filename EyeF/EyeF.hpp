//
//  EyeF.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#ifndef EyeX_EyeF_hpp
#define EyeX_EyeF_hpp

#include "EyeX/EyeX.hpp"

void EyeF_map_fh(
	int l_x, int l_y, float u, float o,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_fa(
	int l_x, int l_y, float u, float o,
	int m_x, int m_y, float v, float p,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_ah(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_ap(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_fp(
	int l_x, int l_y, float u, float o,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_zh(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_hz(
	int n_x, int n_y, float w, float q,
	int m_x, int m_y, float v, float p,
	int32_t map_k[], int16_t map_w[][4])
	;
#endif
