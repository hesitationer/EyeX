//
//  EyeA.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 27/8/15.
//
//

#ifndef EyeX_EyeA_hpp
#define EyeX_EyeA_hpp

#include "EyeX/EyeX.hpp"

typedef struct {
	int l_x;
	int l_y;

	int cen_x;
	int cen_y;
	int rad_o;
	int (*p_o);
	int (*b_o);
	int rad_i;
	int (*p_i);
	int (*b_i);

	int (*ring);
	float (*ring_r);
	int ring_count;

	int m_a;
	int m_r;
	int32_t (*ar_map_k);
	int16_t (*ar_map_w)[4];
}
EyeA;

typedef struct {
	int l_x;
	int l_y;

	int cen_x;
	int cen_y;
	int rad_o;
	int rad_i;

	int count;
	int* p;
	float* r;
}
Ring;

bool Ring_init(Ring& u,
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i);

bool Ring_pr(
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i,
	int p[], float r[], int & count);

bool Ring_h(uint8_t f[], int l_x, int l_y, int p[], float r[], int count);

bool EyeA_init(EyeA & u,
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i);
bool EyeA_s(EyeA & u,
	int s,	EyeA & v);
bool EyeA_s(EyeA & u, int s,
	uint8_t f[], uint8_t w[]);
bool EyeA_ring(EyeA& u);
bool EyeA_h(EyeA& u,
	uint8_t f[]);
//bool EyeA_fea(uint8_t f[], int l_x, int l_y, int p[], int b[], Fea fea[]);
//bool EyeA_w(
//	int p[],
//	int & m_x, int & m_y, int q[]);
//bool EyeA_w(
//	uint8_t f[], int l_x, int l_y, int p[], int b[],
//	uint8_t w[], int m_x, int m_y, int q[]);
//bool EyeA_w(
//	uint8_t f[], int l_x, int l_y, int p[],	int b[],
//	int s,
//	uint8_t w[], int m_x, int m_y, int q[], int d[])
//	;
bool EyeA_init_ar(EyeA & u,
	int m_a, int m_r);
bool EyeA_ar_map(
	int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i,
	int m_a, int m_r,
	int32_t ar_map_k[], int16_t ar_map_w[][4])
	;
bool EyeA_ar(
	uint8_t f[], int l_x, int l_y,
	int32_t ar_map_k[], int16_t ar_map_w[][4],
	uint8_t w[], int m_a, int m_r
	)
	;
bool EyeA_ar(EyeA & u,
	uint8_t f[], uint8_t w[]);
//bool EyeA_ar_info(
//	uint8_t w[], int m_a, int m_r,
//	void* info
//	)
//	;
//
//bool EyeA_A(uint8_t g[], int ma,
//	int mr,
//	int k, float& h)
//	;
//
//bool EyeA_lap(uint8_t f[], int l_x, int l_y, int boundary[][2], uint8_t h[]);

#endif
