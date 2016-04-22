//
//  EyeW_wv.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 27/8/15.
//
//

#include "EyeW.hpp"

bool EyeW_wv_init(EyeW_WV& wv, int n_x, int n_y)
{
	wv.w_1_x = new float[n_x];
	wv.w_1_y = new float[n_y];
	wv.v_1_x = new float[n_x];
	wv.v_1_y = new float[n_y];

	int nn = n_x*n_y;
	wv.w_10 = new float[nn];
	wv.w_01 = new float[nn];
	wv.v_10 = new float[nn];
	wv.v_01 = new float[nn];


	wv.v_0_x = 1.0F;
	wv.v_0_y = 1.0F;
	wv.w_0_x = 1.0F / (wv.v_0_x*n_x);
	wv.w_0_y = 1.0F / (wv.v_0_y*n_y);

	float t;
	for (int k = 0; k < n_x; k++) {
		wv.v_1_x[k] = (float)k;
	}
	t = EyeX::mean(wv.v_1_x, n_x);
	for (int k = 0; k < n_x; k++) {
		wv.v_1_x[k] -= t;
	}
	t = EyeX::prod(wv.v_1_x, wv.v_1_x, n_x);
	for (int k = 0; k < n_x; k++) {
		wv.w_1_x[k] = wv.v_1_x[k] / t;
	}

	for (int k = 0; k < n_y; k++) {
		wv.v_1_y[k] = (float)k;
	}
	t = EyeX::mean(wv.v_1_y, n_y);
	for (int k = 0; k < n_y; k++) {
		wv.v_1_y[k] -= t;
	}
	t = EyeX::prod(wv.v_1_y, wv.v_1_y, n_y);
	for (int k = 0; k < n_y; k++) {
		wv.w_1_y[k] = wv.v_1_y[k] / t;
	}

	wv.w_00 = wv.w_0_x*wv.w_0_y;
	wv.v_00 = wv.v_0_x*wv.v_0_y;
	for (int y = 0; y < n_y; y++) {
		for (int x = 0; x < n_x; x++) {
			wv.w_10[x + y * n_x] = wv.w_1_x[x] * wv.w_0_y;
			wv.v_10[x + y * n_x] = wv.v_1_x[x] * wv.v_0_y;
			wv.w_01[x + y * n_x] = wv.w_0_x * wv.w_1_y[y];
			wv.v_01[x + y * n_x] = wv.v_0_x * wv.v_1_y[y];
		}
	}

	wv.n_x = n_x;
	wv.n_y = n_y;

	return true;
}

bool EyeW_wv_a(EyeW_WV& wv, float f[])
{
	int NN = wv.n_x*wv.n_y;

	float a_00 = 0;
	for (int k = 0; k < NN; k++) {
		a_00 += (f[k] * wv.w_00);
	}

	float a_10 = 0;
	for (int k = 0; k < NN; k++) {
		a_10 += (f[k] * wv.w_10[k]);
	}

	float a_01 = 0;
	for (int k = 0; k < NN; k++) {
		a_01 += (f[k] * wv.w_01[k]);
	}

	wv.a_00 = a_00;
	wv.a_10 = a_10;
	wv.a_01 = a_01;

	return true;
}

bool EyeW_wv_p(EyeW_WV& wv, float p[])
{
	int NN = wv.n_x*wv.n_y;

	for (int k = 0; k < NN; k++) {
		float pk = 0;
		pk += (wv.a_00*wv.v_00);
		pk += (wv.a_10*wv.v_10[k]);
		pk += (wv.a_01*wv.v_01[k]);
		p[k] = pk;
	}

	return true;
}

bool EyeW_wv_e(EyeW_WV & wv, float f[], float p[], float& e)
{
	int NN = wv.n_x*wv.n_y;

	float v = 0;
	for (int k = 0; k < NN; k++) {
		float d = f[k] - p[k];
		v += d*d;
	}
	v /= NN;
	e = v;

	return true;
}

bool EyeW_wv_h(EyeW_WV& wv, uint8_t f[])
{
	int NN = wv.n_x*wv.n_y;

	float a_00 = 0;
	for (int k = 0; k < NN; k++) {
		a_00 += (f[k] * wv.w_00);
	}

	float a_10 = 0;
	for (int k = 0; k < NN; k++) {
		a_10 += (f[k] * wv.w_10[k]);
	}

	float a_01 = 0;
	for (int k = 0; k < NN; k++) {
		a_01 += (f[k] * wv.w_01[k]);
	}

	float p_00 = (a_00*wv.v_00);
	for (int k = 0; k < NN; k++) {
		float p_10 = (a_10*wv.v_10[k]);
		float p_01 = (a_01*wv.v_01[k]);
		f[k] = (uint8_t)roundf(f[k] * p_00 / (p_00 + p_01));
	}

	return true;
}