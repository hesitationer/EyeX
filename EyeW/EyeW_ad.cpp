//
//  EyeW_ad.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 5/12/2016.
//
//

#include "EyeW.hpp"

inline
uint8_t _clipu8(int a)
{
	return a < 0 ? 0 : a > 0xFF ? 0xFF : (uint8_t)a;
}

inline
void _ad(uint8_t f[], int n, uint8_t& u, uint8_t& v)
{
	int a = 0;
	for (int k = 0; k < n; k++) {
		a += f[k];
	}
	a = a / n;
	
	int d = 0;
	for (int k = 0; k < n; k++) {
		d += abs(f[k] - a);
	}
	d /= n;
	
	u = _clipu8(a);
	v = _clipu8(d);
}

bool EyeW_ad(
	uint8_t f[], int l_x, int l_y,
	uint8_t a[], uint8_t d[],
	int n_x, int n_y)
{
	int n = n_x*n_y;
	uint8_t* w = new uint8_t[n];
	
	int i = 0;
	for (int y = 0; y < l_y; y += n_y) {
		for (int x = 0; x < l_x; x += n_x) {
			
			int k = 0;
			for (int j_y = 0; j_y < n_y; j_y++) {
				for (int j_x = 0; j_x < n_x; j_x++) {
					w[k++] = f[(x + j_x) + (y + j_y)*l_x];
				}
			}
			_ad(w, n, a[i], d[i]); i++;
		}
	}

	delete []w;
	return true;
}
