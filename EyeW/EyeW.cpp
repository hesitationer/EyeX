#include "EyeW.hpp"

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
