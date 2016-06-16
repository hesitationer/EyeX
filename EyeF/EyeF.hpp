//
//  EyeF.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

// f: fisheye
// g: grid
// a: angle
// s: sphere
// c: cylinder
// v: view

#ifndef EyeX_EyeF_hpp
#define EyeX_EyeF_hpp

#include "EyeX.hpp"

typedef enum {
	A,
	F,
	G,
}
AGF;

typedef struct {
	float fov_x, fov_y;
	AGF type;
	int l_x, l_y;
	float v_x, v_y;
	float x_n, x_p, y_n, y_p;
}
Fov;

void fov_init(Fov& fov, float fov_x, float fov_y, AGF type, float v_x = 0, float v_y = 0)
;
void EyeF_map_fg(Fov& fov_f, Fov& fov_g,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
	;
	
void EyeF_map_fg(
	int l_x, int l_y, float u, float o,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_fa(
	int l_x, int l_y, float u, float o,
	int m_x, int m_y, float v, float p,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_ag(
	int m_x, int m_y, float v, float p,
	int n_x, int n_y, float w, float q,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_ah(
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
