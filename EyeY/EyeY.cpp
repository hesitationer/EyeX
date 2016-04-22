//
//  EyeY.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 27/8/15.
//
//

#include "_EyeY.hpp"
#include "EyeP/EyeP.hpp"
#include <cmath>

bool EyeY_boundary(
	int cen_x, int cen_y, int rad,
	int16_t boundary[][2])
{
	int rr = rad*rad;
	int r_x, r_y;
	boundary[0][0] = cen_y - rad;
	boundary[0][1] = cen_y + rad;
	int k = 1;
	for (int y = boundary[0][0]; y <= boundary[0][1]; y++) {
		r_y = abs(y - cen_y);
		r_x = (int)(sqrt(rr - r_y*r_y)+0.5F);
		boundary[k][0] = cen_x - r_x;
		boundary[k][1] = cen_x + r_x;
		k++;
	}

	return true;
}

bool EyeY_hist(uint8_t im[], int l_x, int l_y, int16_t boundary[][2])
{
	int y_0 = boundary[0][0];
	int y_1 = boundary[0][1];
	int k = 1;
	for (int y = y_0; y <= y_1; y++) {
		int x_0 = boundary[k][0];
		int x_1 = boundary[k][1];
		k++;
		for (int x = x_0; x <= x_1; x++) {
			im[x + y*l_x] = 0xFF;
		}
	}

	return true;
}

bool EyeY_ar_map(
	int l_x, int l_y, int cen_x, int cen_y, int rad,
	int m_a, int m_r, int rad_in, int rad_ex,
	int32_t ar_map_k[], int16_t ar_map_w[][4])
{
	float w_r = (float)(rad_ex - rad_in) / m_r;
	float w_a = PI2 / m_a;
	float y_r, y_a;
	float f_x, f_y;
	for (int j = 0, r = 0; r<m_r; r++) {
		y_r = w_r * (r + 0.5F) + rad_in;
		for (int a = 0; a<m_a; a++, j++) {
			y_a = w_a * (a + 0.5F);
			_yf(y_r, y_a, f_x, f_y);
			float t_x = f_x + cen_x;
			float t_y = f_y + cen_y;
			int k_x, k_y;
			int16_t w_0, w_1, w_2, w_3;
			EyeP_kw(t_x, t_y, k_x, k_y, w_0, w_1, w_2, w_3);
			ar_map_k[j] = k_x + k_y*l_x;
			ar_map_w[j][0] = w_0;
			ar_map_w[j][1] = w_1;
			ar_map_w[j][2] = w_2;
			ar_map_w[j][3] = w_3;
		}
	}

	return true;
}

bool EyeY_ar(
	uint8_t f[], int l_x, int l_y,
	int32_t ar_map_k[], int16_t ar_map_w[][4],
	uint8_t g[], int m_a, int m_r
	) {
	EyeP_remap_w(f, l_x, l_y, g, m_a, m_r, ar_map_k, ar_map_w);

	return true;
}

bool EyeY_ar_info(uint8_t w[], int m_a, int m_r, void * info)
{
	int16_t* z = (int16_t*)info;
	int hist[256];
	uint8_t* p;
	for (int r = 0; r < m_r; r++) {
		p = &w[r*m_a];
		for (int i = 0; i < 256; i++) {
			hist[i] = 0;
		}
		for (int a = 0; a < m_a; a++) {
			hist[p[a]]++;
		}
		uint8_t v = 0;
		int h = hist[v];
		for (int i = 1; i < 256; i++) {
			if (h < hist[i]) {
				v = i;
				h = hist[v];
			}
		}
		z[r] = v;
	}

	return true;
}

void _mod(float& a, float d)
{
	float f = a / d;
	a = f - floorf(f);
}

bool EyeY_A(uint8_t g[], int m_a,
			int m_r,
			int k, float& t)
{
	float w = PI2 / m_a;
	float d = PI2 / k;
	float p, q;
	float f0 = 0, f_x = 0;
//	for (int j=0,r=0; r<m_r; r++) {
//		for (int a=0; a<m_a; a++,j++) {
//			p = g[j];
//			q = w * (a + 0.5F);
//			_mod(q, d);
//			
//			f0 += p*p;
//			f_x += p*p*q;
//		}
//	}
	float* s = new float[m_a];
	for (int a=0; a<m_a; a++) {
		p = 0;
		for (int r=0; r<m_r; r++) {
			p += g[a + r*m_a];
		}
		s[a] = p;
	}
	for (int a=0; a<m_a; a++) {
		p = s[a];
		q = w * (a + 0.5F);
		_mod(q, d);
		f0 += p;
		f_x += p*q;
	}
	
	t = f_x / f0;

	return true;
}

bool EyeY_lap(
	uint8_t f[], int l_x, int l_y,
	int16_t boundary[][2],
	uint8_t h[])
{
	int y_0 = boundary[0][0];
	int y_1 = boundary[0][1];
	int k = 1;
	for (int y = y_0; y <= y_1; y++) {
		int x_0 = boundary[k][0];
		int x_1 = boundary[k][1];
		k++;
		for (int x = x_0; x <= x_1; x++) {
			int16_t lap;
			_Fea _fea;
			Fea fea = &_fea;
			EyeX_fea(f, l_x, l_y, x, y, fea);
			lap = abs(fea->gra);
			//h[x + y*l_x] = (uint8_t)(lap);

			if (lap > 6) h[x + y*l_x] = 0xFF;
		}
	}

	return true;
}
