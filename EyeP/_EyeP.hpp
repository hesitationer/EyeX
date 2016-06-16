//
//  _EyeP.hpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#ifndef _EyeX_EyeP_hpp
#define _EyeX_EyeP_hpp

#include "EyeP.hpp"
#include <math.h>
#include <float.h>

const int _SR = 12;

inline
int16_t _s(float f)
{
	return (int16_t)(f * (1 << _SR) + 0.5F);
}

inline
uint8_t _r(int a)
{
	return (uint8_t)(a >> _SR);
}

#endif
