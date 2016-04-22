#pragma once

#include "EyeX/_EyeX.hpp"

namespace EyeW {
	const int N = 64;
	const int NN = N*N;
}

typedef struct {
	int n_x, n_y;

	float w_0_x;
	float w_0_y;
	float v_0_x;
	float v_0_y;
	float* w_1_x;
	float* w_1_y;
	float* v_1_x;
	float* v_1_y;

	float w_00;
	float v_00;
	float* w_10;
	float* v_10;
	float* w_01;
	float* v_01;

	float a_00;
	float a_10;
	float a_01;
}
EyeW_WV;

bool EyeW_wv_init(EyeW_WV& wv, int n_x, int n_y);
bool EyeW_wv_a(EyeW_WV & wv, float f[]);
bool EyeW_wv_p(EyeW_WV & wv, float p[]);
bool EyeW_wv_e(EyeW_WV & wv, float f[], float p[], float & e);
bool EyeW_wv_h(EyeW_WV& wv, uint8_t f[]);
bool EyeW_he(uint8_t f[], uint8_t d[], uint8_t h[], uint8_t e[]);
bool EyeW_init();
