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
const float _dr = PI / 180 / 2;

inline
float DR(float deg) { return _dr*deg; }

#endif
