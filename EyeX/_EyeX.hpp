//
//  _EyeX.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#ifndef _EyeX_EyeX_hpp
#define _EyeX_EyeX_hpp

#include "EyeX.hpp"

const int _SR = 1 << 12;

inline
int _s(float f)
{
	return (int)roundf(f * _SR);
}

inline
int _r(int a)
{
	return (int)(a / _SR);
}

namespace EyeX {

inline
float mean(float u[], int n)
{
	float a = 0;
	for (int k = 0; k < n; k++) {
		a += u[k];
	}
	a /= n;

	return a;
}

inline
float prod(float u[], float v[], int n)
{
	float a = 0;
	for (int k = 0; k < n; k++) {
		a += u[k] * v[k];
	}

	return a;
}

inline
float norm(float u[], int n)
{
	float a = 0;
	for (int k = 0; k < n; k++) {
		a += u[k] * u[k];
	}
	a = sqrtf(a);

	return a;
}

}

#endif
