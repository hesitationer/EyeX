// EyeX.cpp

#include "_EyeX.hpp"

bool EyeX_fea(
	uint8_t f[], int l_x, int l_y,
	int x, int y,
	void* p)
{
	Fea* fea = (Fea*)p;

	int i = x + y*l_x;
	uint8_t
		f_nn = f[i - 1 - l_x], f_on = f[i - 1], f_mn = f[i - 1 + l_x],
		f_no = f[i     - l_x], f_oo = f[i    ], f_mo = f[i     + l_x],
		f_nm = f[i + 1 - l_x], f_om = f[i + 1], f_mm = f[i + 1 + l_x];
	int d_x = (((f_mo - f_no) >> 1) + ((f_mn + f_mm) - (f_nn + f_nm))) >> 3;
	int d_y = (((f_om - f_on) >> 1) + ((f_nm + f_mm) - (f_nn + f_mn))) >> 3;
	int16_t gra = (int16_t)sqrt(d_x*d_x + d_y*d_y);
	int16_t lap = (((f_no + f_mo + f_on + f_om) + (f_nn + f_mn + f_nm + f_mm)) >> 3) - f_oo;
	fea->gra = gra;
	fea->lap = lap;

	return true;
}