//
//  main.cpp
//  appEyeF
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#include "EyeF.hpp"
#include "EyeP.hpp"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace cv;

const float _PI = atan(1.0F)*4;
const float _A = _PI/360*135;

int main_yuv(int argc, const char * argv[]) {
	// parameters of YUV frames from capture
	int l1 = 1280;
	int l2 =  960;
	int l = l1*l2;
	int m1 = 1136;
	int m2 =  640;
	int m = m1*m2;

	char folder[256] = { "/Users/zhongsifen/Work/data/zhuxin/" };
	char name[80] = { "fisheye_1_1280x960" };
	char ext[8] = { ".yuv" };
	char tname[80] = { "fisheye_0" };
	int k=1;
	if (k < argc) sscanf(argv[k++], "%s", folder);
	if (k < argc) sscanf(argv[k++], "%s", name);
	if (k < argc) sscanf(argv[k++], "%s", ext);
	if (k < argc) sscanf(argv[k++], "%s", tname);
	if (k < argc) sscanf(argv[k++], "%d", &l1);
	if (k < argc) sscanf(argv[k++], "%d", &l2);
	char filename_inp[256];
	char filename_out[256];
	sprintf(filename_inp, "%s%s%s", folder, name, ext);
	sprintf(filename_out, "%s%s_%dx%d%s", folder, tname, m1, m2, ext);
	FILE* file_inp = fopen(filename_inp, "rb");
	FILE* file_out = fopen(filename_out, "wb");
	
	uint8_t* f_yuv = new uint8_t[l*3/2];
	uint8_t* f_y = f_yuv;
	uint8_t* f_u = f_y + l;
	uint8_t* f_v = f_u + l/4;
	uint8_t* g_yuv = new uint8_t[m*3/2];
	uint8_t* g_y = g_yuv;
	uint8_t* g_u = g_y + m;
	uint8_t* g_v = g_u + m/4;

	// parameters of YUV frames from capture 
	float f_fov = _A;
	float f_pov = 0;
	// parameters of YUV frames for display
	float g_fov[] = {
		_A,
		_A*3/4,
		_A*3/4,
		_A*3/4,
		_A*2/3,
		_A*2/3,
		_A*2/3,
	};
	float g_pov[] = {
		0,
		0,
		_A*(+1.0F/4),
		_A*(-1.0F/4),
		0,
		_A*(+1.0F/3),
		_A*(-1.0F/3),
	};
	int32_t (*map_k) = new int32_t[m];
	int16_t (*map_w)[4] = new int16_t[m][4];
	int32_t (*map_n) = new int32_t[m/4];
	int16_t (*map_z)[4] = new int16_t[m/4][4];

	for (int view=0; view<4; view++)
	{
		EyeF_map_pov(l1, l2, f_fov, f_pov, m1, m2, g_fov[view], g_pov[view], map_k, map_w, map_n, map_z);

		for (int k=0; k<100; k++) {
			fread(f_yuv, l*3/2, 1, file_inp);

			EyeP_remap_yuv(f_y, f_u, f_v, l1, l2, g_y, g_u, g_v, m1, m2, map_k, map_w, map_n, map_z);

			fwrite(g_yuv, m*3/2, 1, file_out);
		}
	}

	fclose(file_inp);
	fclose(file_out);
	delete[] map_k;
	delete[] map_w;
	delete[] map_n;
	delete[] map_z;
	delete[] f_yuv;
	delete[] g_yuv;

	printf("Hello, world! This is gamma.\n");
	return 0;
}
