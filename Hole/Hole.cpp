// EyeHole.cpp

#include "Hole.hpp"
#include <cmath>

bool hole_circle(
	int l_x, int l_y, int cen_x, int cen_y, int rad_o,
	int p[], float r[], int& count)
{
	int n = 0;
	float r_x, r_y;
	float rr_o = (float)(rad_o * rad_o);
	int y_0 = cen_y - rad_o;
	int y_3 = cen_y + rad_o;
	for (int y = y_0; y <= y_3; y++) {
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

bool hole_ring(
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

bool hole_flatten(
	uint8_t f[], int l_x, int l_y,
	int p[], float r[], int count,
	bool valid[],
	uint8_t g[], uint8_t h[], uint8_t e[])
{
	float sf = 0;
	float sr = 0;
	float rf = 0;
	float rr = 0;
	int n = 0;
	for (int k = 0; k < count; k++) {
		if (valid[k]) {
			float r_k = r[k];
		float f_k = f[p[k]];
		sf += f_k;
		sr += r_k;
		rf += r_k*f_k;
		rr += r_k*r_k;

		n++;
		}
	}
	float af = sf / count;
	float ar = sr / count;

	float s = (rf - sr*af) / (rr - sr*ar);
	float t = af - ar*s;
	for (int k = 0; k < count; k++) {
		int p_k = p[k];
		h[p_k] = (uint8_t)round(t + r[k]*s);
		e[p_k] = abs(h[p_k] - f[p_k]);
		g[p_k] = f[p_k] + 0xA0 - h[p_k];
		valid[p_k] = e[p_k] < 40;
	}

	return true;
}

bool hole_hist(
	uint8_t f[], int p[], int count,
	int hist[256])
{
	for (int i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (int k = 0; k < count; k++) {
		hist[f[p[k]]]++;
	}

	return true;
}
