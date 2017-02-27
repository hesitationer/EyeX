#include "EyeW.hpp"

inline
bool _he(int f[], int p[], int l, int& h, int& e)
{
	int a;
	int v;

	a = 0;
	for (int k = 0; k < l; k++) {
		a += f[k];
	}
	a = a / l;
	h = a;

	for (int k = 0; k < l; k++) {
		p[k] = a;
	}

	v = 0;
	for (int k = 0; k < l; k++) {
		int d = f[k] - a;
		v += d*d;
	}
	v /= l;
	e = v;

	return true;
}

bool EyeW_he(
	uint8_t f[], int l_x, int l_y,
	uint8_t t[],
	uint8_t h[], uint8_t e[])
{
	int m_x = l_x / 4;
	int m_y = l_x / 4;

	int w[16], p[16], hi, ei;
	int i = 0;
	for (int y = 0; y < l_y; y += 4) {
		for (int x = 0; x < l_x; x += 4) {

			int k = 0;
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					w[k++] = f[(x + i) + (y + j)*l_x];
				}
			}
			_he(w, p, 16, hi, ei);
			k = 0;
			for (int j = 0; j < 4; j++) {
				for (int i = 0; i < 4; i++) {
					t[(x + i) + (y + j)*l_x] = p[k];
				}
			}
			h[i] = hi; e[i] = ei; i++;
		}
	}

	return true;
}

bool EyeW_w(
	int16_t f[], int l_x, int l_y,
	int x, int y,
	int16_t h_w[], int16_t h_x[], int16_t h_y[], int16_t h_z[])
{
	int m_x = l_x / 2;
	int m_y = l_y / 2;
	int i = (x    ) + (y    )*l_x;
	int j = (x / 2) + (y / 2)*m_x;

	int f_nn = f[i];
	int f_pn = f[i + 1];
	int f_np = f[i     + l_x];
	int f_pp = f[i + 1 + l_x];
			
	h_w[j] = (f_nn + f_pn + f_np + f_pp);
	h_x[j] = (f_nn - f_pn + f_np - f_pp);
	h_y[j] = (f_nn + f_pn - f_np - f_pp);
	h_z[j] = (f_nn - f_pn - f_np + f_pp);

	return true;
}
