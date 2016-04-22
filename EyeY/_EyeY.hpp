//
//  _EyeY.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 27/8/15.
//
//

#ifndef EyeX__EyeY_hpp
#define EyeX__EyeY_hpp

#include "EyeX/_EyeX.hpp"
#include "EyeY.hpp"

inline
void _yf(float yr, float ya,
		 float& f1, float& f2)
{
	f1 = yr * cos(ya);
	f2 = yr * sin(ya);
}

inline
void _fy(float f1, float f2,
		 float& yr, float& ya)
{
	yr = sqrtf(f1*f1 + f2*f2);
	ya = atan2f(f2, f1);
}

#endif
