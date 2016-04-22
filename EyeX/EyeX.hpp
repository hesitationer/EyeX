//
//  EyeX.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#ifndef EyeX_EyeX_hpp
#define EyeX_EyeX_hpp

#include <string>
#include <cstdint>
#include <cmath>
#include <cassert>

const static std::string DATA_EYEX("/Users/zhongsifen/Data/eyex/");

const float PI = atanf(1.0F)*4;
const float PI2 = PI*2;

typedef struct {
	int16_t gra;
	int16_t lap;
}
Fea;

#endif

bool EyeX_fea(
	uint8_t f[], int l_x, int l_y,
	int x, int y,
	void* fea)
	;
