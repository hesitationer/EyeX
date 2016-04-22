//
//  EyeY.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 27/8/15.
//
//

#ifndef EyeX_EyeY_hpp
#define EyeX_EyeY_hpp

#include "EyeX/EyeX.hpp"

typedef struct {
	int l_x;
	int l_y;

	int cen_x;
	int cen_y;
	int rad;
	int rad_in;
	int rad_ex;

	int m_a;
	int m_r;

	int32_t (*ar_map_k);
	int16_t (*ar_map_w)[4];

	int16_t (*boundary)[2];
}
EyeY;

bool EyeY_boundary(
	int cen_x, int cen_y, int rad,
	int16_t boundary[][2])
	;
bool EyeY_hist(
	uint8_t im[], int l_x, int l_y,
	int16_t boundary[][2])
	;
bool EyeY_ar_map(
	int l_x, int l_y, int cen_x, int cen_y, int rad,
	int m_a, int m_r, int rad_in, int rad_ex,
	int32_t ar_map_k[], int16_t ar_map_w[][4])
	;
bool EyeY_ar(
	uint8_t f[], int l_x, int l_y,
	int32_t ar_map_k[], int16_t ar_map_w[][4],
	uint8_t w[], int m_a, int m_r
	)
	;
bool EyeY_ar_info(
	uint8_t w[], int m_a, int m_r,
	void* info
	)
	;

bool EyeY_A(uint8_t g[], int ma,
			int mr,
			int k, float& h)
	;

bool EyeY_lap(uint8_t f[], int l_x, int l_y, int16_t boundary[][2], uint8_t h[]);

#endif
