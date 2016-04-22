//
//  EyeA.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 27/8/15.
//
//

#include "EyeA.hpp"
#include <cmath>

inline
void _ar_xy(float a, float r, float& x, float& y)
{
	x = cos(a)*r;
	y = sin(a)*r;
}

inline
void _xy_ar(
	float x, float y,
	float& a, float& r)
{
	a = atan2f(y, x);	if (a < 0) a += PI2;
	r = sqrtf(x*x + y*y);
}

#include "EyeA.hpp"
#include "EyeP/EyeP.hpp"
#include <cmath>

bool EyeA_p(int cen_x, int cen_y, int rad, int p[])
{
	p[0] = cen_x - rad;
	p[1] = cen_y - rad;
	p[2] = cen_x + rad + 1;
	p[3] = cen_y + rad + 1;

	return true;
}

bool EyeA_b(int cen_x, int cen_y, int rad, int b[])
{
	int lt_x = cen_x - rad;
	int rb_x = cen_x + rad + 1;
	int lt_y = cen_y - rad;
	int rb_y = cen_y + rad + 1;

	int k = 0;
	float c_x = cen_x + 0.5F;
	float c_y = cen_y + 0.5F;
	float r = rad + 0.5F;
	float rr = r*r;
	float r_x, r_y;
	for (int y = lt_y; y <= rb_y; y++) {
		r_y = (float)(c_y - y);
		r_x = sqrtf(rr - r_y*r_y);
		b[k++] = (int)round(c_x - lt_x - r_x);
		b[k++] = (int)round(c_x - lt_x + r_x);
	}

	return true;
}

bool Ring_init(Ring& u,
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i)
{
	u.l_x = l_x;
	u.l_y = l_y;
	u.cen_x = cen_x;
	u.cen_y = cen_y;
	u.rad_o = rad_o;
	u.rad_i = rad_i;

	return true;
}

bool Ring_pr(
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i,
	int p[], float r[], int& count)
{
	int n = 0;
	float r_x, r_y;
	float rr_o = (float)(rad_o * rad_o);
	float rr_i = (float)(rad_i * rad_i);
	int y_0 = cen_y - rad_o;
	int y_1 = cen_y - rad_i;
	int y_2 = cen_y + rad_i;
	int y_3 = cen_y + rad_o;
	for (int y = y_0; y < y_1; y++) {
		r_y = (float)(cen_y - y);
		r_x = sqrtf(rr_o - r_y*r_y);
		int x_0 = (int)round(cen_x - r_x);
		int x_3 = (int)round(cen_x + r_x);
		for (int x = x_0; x <= x_3; x++) {
			int xp = x - cen_x;
			int yp = y - cen_y;
			r[n] = sqrtf((float)(xp*xp + yp*yp));
			p[n++] = x + y*l_x;
		}
	}
	for (int y = y_1; y <= y_2; y++) {
		r_y = (float)(cen_y - y);
		r_x = sqrtf(rr_o - r_y*r_y);
		int x_0 = (int)round(cen_x - r_x);
		int x_3 = (int)round(cen_x + r_x);
		r_x = sqrtf(rr_i - r_y*r_y);
		int x_1 = (int)round(cen_x - r_x);
		int x_2 = (int)round(cen_x + r_x);
		for (int x = x_0; x <= x_1; x++) {
			int xp = x - cen_x;
			int yp = y - cen_y;
			r[n] = sqrtf((float)(xp*xp + yp*yp));
			p[n++] = x + y*l_x;
		}
		for (int x = x_2; x <= x_3; x++) {
			int xp = x - cen_x;
			int yp = y - cen_y;
			r[n] = sqrtf((float)(xp*xp + yp*yp));
			p[n++] = x + y*l_x;
		}
	}
	for (int y = y_2 + 1; y <= y_3; y++) {
		r_y = (float)(cen_y - y);
		r_x = sqrtf(rr_o - r_y*r_y);
		int x_0 = (int)round(cen_x - r_x);
		int x_3 = (int)round(cen_x + r_x);
		for (int x = x_0; x <= x_3; x++) {
			int xp = x - cen_x;
			int yp = y - cen_y;
			r[n] = sqrtf((float)(xp*xp + yp*yp));
			p[n++] = x + y*l_x;
		}
	}
	count = n;

	return true;
}

bool Ring_h(uint8_t f[], int l_x, int l_y, int p[], float r[], int count)
{
	float sf = 0;
	float sr = 0;
	for (int k = 0; k < count; k++) {
		sf += f[p[k]];
		sr += r[k];
	}
	float af = sf / count;
	float ar = sr / count;

	float rf = 0;
	float rr = 0;
	for (int k = 0; k < count; k++) {
		float r_k = r[k];
		rf += r_k*f[p[k]];
		rr += r_k*r_k;
	}

	float s = (rf - sr*af) / (rr - sr*ar);
	float t = af - 0x80;
	for (int k = 0; k < count; k++) {
		f[p[k]] -= (uint8_t)round(t + (r[k] - ar)*s);
		//f[p[k]] = (uint8_t)round(((float)f[p[k]] * af) / (af + (r[k] - ar)*s));
	}

	return true;
}

bool EyeA_init(EyeA& u, int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i)
{
	u.l_x = l_x;
	u.l_y = l_y;
	u.cen_x = cen_x;
	u.cen_y = cen_y;
	u.rad_o = rad_o;
	u.rad_i = rad_i;

	u.p_o = new int[4];
	u.p_i = new int[4];
	EyeA_p(u.cen_x, u.cen_y, u.rad_o, u.p_o);
	EyeA_p(u.cen_x, u.cen_y, u.rad_i, u.p_i);

	u.b_o = new int[(rad_o + 1) * 2 * 2];
	u.b_i = new int[(rad_i + 1) * 2 * 2];
	EyeA_b(u.cen_x, u.cen_y, u.rad_o, u.b_o);
	EyeA_b(u.cen_x, u.cen_y, u.rad_i, u.b_i);

	u.ring = new int[u.l_x*u.l_y];
	u.ring_r = new float[u.l_x*u.l_y];
	EyeA_ring(u);

	return true;
}

bool EyeA_ring(EyeA& u)
{
	int* ring = u.ring;
	float* ring_r = u.ring_r;
	float c_x = u.cen_x + 0.5F;
	float c_y = u.cen_y + 0.5F;

	int y_0 = u.p_o[1];
	int y_1 = u.p_i[1];
	int y_2 = u.p_i[3];
	int y_3 = u.p_o[3];
	int k = 0;
	int n = 0;
	for (int y = y_0; y < y_1; y++) {
		int x_0 = u.b_o[k++] + u.p_o[0];
		int x_3 = u.b_o[k++] + u.p_o[0];
		for (int x = x_0; x <= x_3; x++) {
			float xp = x - c_x;
			float yp = y - c_y;
			ring_r[n] = sqrtf(xp*xp + yp*yp);
			ring[n++] = x + y*u.l_x;
		}
	}
	int j = 0;
	for (int y = y_1; y <= y_2; y++) {
		int x_0 = u.b_o[k++] + u.p_o[0];
		int x_1 = u.b_i[j++] + u.p_i[0];
		int x_2 = u.b_i[j++] + u.p_i[0];
		int x_3 = u.b_o[k++] + u.p_o[0];
		for (int x = x_0; x <= x_1; x++) {
			float xp = x - c_x;
			float yp = y - c_y;
			ring_r[n] = sqrtf(xp*xp + yp*yp);
			ring[n++] = x + y*u.l_x;
		}
		for (int x = x_2; x <= x_3; x++) {
			float xp = x - c_x;
			float yp = y - c_y;
			ring_r[n] = sqrtf(xp*xp + yp*yp);
			ring[n++] = x + y*u.l_x;
		}
	}
	for (int y = y_2 + 1; y <= y_3; y++) {
		int x_0 = u.b_o[k++] + u.p_o[0];
		int x_3 = u.b_o[k++] + u.p_o[0];
		for (int x = x_0; x <= x_3; x++) {
			float xp = x - c_x;
			float yp = y - c_y;
			ring_r[n] = sqrtf(xp*xp + yp*yp);
			ring[n++] = x + y*u.l_x;
		}
	}
	u.ring_count = n;

	return true;
}

bool EyeA_h(EyeA& u,
	uint8_t f[])
{
	float c_x = u.cen_x + 0.5F;
	float c_y = u.cen_y + 0.5F;

	float sf = 0;
	float sr = 0;
	for (int k = 0; k < u.ring_count; k++) {
		sf += f[u.ring[k]];
		sr += u.ring_r[k];
	}
	float af = sf / u.ring_count;
	float ar = sr / u.ring_count;

	float rf = 0;
	float rr = 0;
	for (int k = 0; k < u.ring_count; k++) {
		float r = u.ring_r[k];
		rf += r*f[u.ring[k]];
		rr += r*r;
	}

	float s = (rf - sr*af) / (rr - sr*ar);
	float t = af - 0x80;
	for (int k = 0; k < u.ring_count; k++) {
		f[u.ring[k]] -= (uint8_t)round(t + (u.ring_r[k]-ar)*s);
		//f[u.ring[k]] = (uint8_t)round(((float)f[u.ring[k]] * af) / (af + (u.ring_r[k] - ar)*s));
	}

	return true;
}

bool EyeA_init_ar(EyeA& u, int m_a, int m_r)
{
	u.m_a = m_a < 0 ? (int)(u.rad_o * PI2) : m_a;
	u.m_r = m_r < 0 ? u.rad_o - u.rad_i : m_r;
	u.ar_map_k = new int32_t[u.m_a*u.m_r];
	u.ar_map_w = new int16_t[u.m_a*u.m_r][4];
	EyeA_ar_map(u.l_x, u.l_y, u.cen_x, u.cen_y, u.rad_o, u.rad_i, u.m_a, u.m_r, u.ar_map_k, u.ar_map_w);

	return true;
}


bool EyeA_s(EyeA& u,
	int s,	EyeA& v)
{
	EyeA_init(v, u.l_x / s, u.l_y / s, u.cen_x / s, u.cen_y / s, u.rad_o / s, u.rad_i / s);

	return true;
}

bool EyeA_s(EyeA & v, int s,
	uint8_t f[], uint8_t w[])
{
	int l_x = v.l_x;
	int l_y = v.l_y;
	int n_x = l_x*s;
	int n_y = l_y*s;
	int ss = s*s;
	int k = 0;
	for (int y = v.p_o[1]; y <= v.p_o[3]; y++) {
		int ys = y*s;
		int x_0 = v.b_o[k++] + v.p_o[0];
		int x_1 = v.b_o[k++] + v.p_o[0];
		for (int x = x_0; x <= x_1; x++) {
			int xs = x*s;
			int a = 0;
			for (int j = 0; j < s; j++) {
				for (int i = 0; i < s; i++) {
					a += f[(xs + i) + (ys + j)*n_x];
				}
			}
			w[(x)+(y)*l_x] = a / ss;
		}
	}

	return true;
}

bool EyeA_fea(uint8_t f[], int l_x, int l_y, int p[], int b[], Fea fea[])
{
	uint8_t* fy = &f[p[1] * l_x];
	Fea* feay = &fea[p[1] * l_x];
	int k = 0;
	for (int y = p[1]; y <= p[3]; y++) {
		int x_0 = b[k++] + p[0];
		int x_1 = b[k++] + p[0];
		for (int x = x_0; x <= x_1; x++) {
			EyeX_fea(f, l_x, l_y, x, y, &fea[x]);
		}
		fy += l_x;
		feay += l_x;
	}

	return true;
}

bool EyeA_w(
	uint8_t f[], int l_x, int l_y, int p[], int b[],
	uint8_t w[], int m_x, int m_y, int q[])
{
	uint8_t* fy = &f[p[1] * l_x];
	uint8_t* wy = &w[q[1] * m_y];
	int k = 0;
	for (int y = p[1]; y <= p[3]; y++) {
		int x_n = b[k++];
		int x_p = b[k++];
		for (int x = x_n; x < x_p; x++) {
			wy[x + q[0]] = fy[x + p[0]];
		}
		fy += l_x;
		wy += m_x;
	}

	return true;
}

bool EyeA_w(
	uint8_t f[], int l_x, int l_y, int p[],	int b[],
	int s,
	uint8_t w[], int m_x, int m_y, int q[], int d[])
{
	uint8_t* fy = &f[p[1]*l_x];
	uint8_t* wy = &w[q[1]*m_y];
	int k = 0;
	for (int y = p[1]; y <= p[3]; y++) {
		int x_n = b[k++];
		int x_p = b[k++];
		for (int x = x_n; x < x_p; x++) {
			wy[x + q[0]] = fy[x + p[0]];
		}
		fy += l_x;
		wy += m_x;
	}

	return true;
}

bool EyeA_www(
	uint8_t f[], int l_x, int l_y, int p[],
	int b[],
	uint8_t w[], int m_x, int m_y, int q[])
{
	uint8_t* fy = &f[p[1] * l_x];
	uint8_t* wy = &w[q[1] * m_y];
	int k = 0;
	for (int y = p[1]; y <= p[3]; y++) {
		int x_n = b[k++];
		int x_p = b[k++];
		for (int x = x_n; x < x_p; x++) {
			wy[x + q[0]] = fy[x + p[0]];
		}
		fy += l_x;
		wy += m_x;
	}

	return true;
}

bool EyeA_ar_map(
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i,
	int m_a, int m_r,
	int32_t ar_map_k[], int16_t ar_map_w[][4])
{
	float w_r = (float)(rad_o - rad_i) / m_r;
	float w_a = PI2 / m_a;
	float y_r, y_a;
	float f_x, f_y;
	for (int j = 0, r = 0; r<m_r; r++) {
		y_r = w_r * (r + 0.5F) + rad_i;
		for (int a = 0; a<m_a; a++, j++) {
			y_a = w_a * (a + 0.5F);
			_ar_xy(y_a, y_r, f_x, f_y);
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

bool EyeA_ar(
	uint8_t f[], int l_x, int l_y,
	int32_t ar_map_k[], int16_t ar_map_w[][4],
	uint8_t g[], int m_a, int m_r
	) {
	EyeP_remap_w(f, l_x, l_y, g, m_a, m_r, ar_map_k, ar_map_w);

	return true;
}

bool EyeA_ar(EyeA & u,
	uint8_t f[], uint8_t w[])
{
	EyeP_remap_w(f, u.l_x, u.l_y, w, u.m_a, u.m_r, u.ar_map_k, u.ar_map_w);

	return true;
}
