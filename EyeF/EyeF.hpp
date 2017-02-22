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

typedef enum {
	A,
	F,
	G,
	H,
}
AGF;

typedef struct {
	float x_n, x_p, y_n, y_p;
	float x_o, y_o;
	float delta;
}
Rov;

typedef struct {
	int l_x, l_y;
	float fov;
	float pov_x, pov_y;
	AGF type;
	Rov rov_a, rov_f, rov_g, rov_h;
}
Fisheye;

void fisheye_init(Fisheye& fisheye, int l_x, int l_y, float fov, AGF type, float pov_x = 0, float pov_y = 0)
;
void EyeF_map_fg(Fisheye& fov_f, Fisheye& fov_g,
	int l_x, int l_y, int n_x, int n_y,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_fh(Fisheye& fov_f, Fisheye& fov_h,
	int l_x, int l_y, int n_x, int n_y,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_fa(Fisheye& fov_f, Fisheye& fov_a,
	int l_x, int l_y, int m_x, int m_y,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_ag(Fisheye& fov_a, Fisheye& fov_g,
	int m_x, int m_y, int n_x, int n_y,
	int32_t map_k[], int16_t map_w[][4])
	;
void EyeF_map_ah(Fisheye& fov_a, Fisheye& fov_h,
	int l_x, int l_y, int n_x, int n_y,
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
