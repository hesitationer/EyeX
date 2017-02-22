//
//  fisheye.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 29/10/2016.
//
//

#ifndef _Fisheye_hpp_
#define _Fisheye_hpp_

#include <cstdint>

typedef struct {
	int l_x, l_y;
	float fov;

	float z_x, z_y;
	float r_x, r_y;
	float cnr[8];
}
FL;

typedef struct {
	FL camera;
	FL display;
	float pov_x, pov_y;
	float cnr_o[8];
	float cnr_p[8];
	int32_t(*map_k);
	int16_t(*map_w)[4];
}
FD;

bool Fisheye_camera(FD& fd, int l_x, int l_y, int ln_x, int ln_y, int lp_x, int lp_y, float fov)
;
bool Fisheye_display(FD& fd, int l_x, int l_y, float fov)
;
bool Fisheye_setup(FD& fd, float pov_x=0, float pov_y=0)
;
bool Fisheye_run(FD& fd, uint8_t f[], uint8_t g[])
;
bool Fisheye_setup_135(FD& fd, float pov_x = 0, float pov_y = 0)
;

#endif // !_Fisheye_h_
