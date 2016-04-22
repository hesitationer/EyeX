// Hole.hpp

#pragma once
#include <cstdint>

namespace hole {
	const int l_x = 1920;
	const int l_y = 1920;

	const int cen_x = 992;
	const int cen_y = 920;
	const int rad_o = 800;		//816
	const int rad_i = 192;
}

bool hole_circle(int l_x, int l_y, int cen_x, int cen_y, int rad_o, int p[], float r[], int & count);

bool hole_ring(int l_x, int l_y, int cen_x, int cen_y, int rad_o, int rad_i, int p[], float r[], int & count);

bool hole_flatten(uint8_t f[], int l_x, int l_y, int p[], float r[], int count, uint8_t g[], uint8_t h[], uint8_t e[]);

bool hole_hist(uint8_t f[], int p[], int count, int hist[256]);
