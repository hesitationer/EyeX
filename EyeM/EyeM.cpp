//
//  EyeM.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 20/10/2016.
//
//

#include "EyeM.hpp"
using namespace EyeX;

bool EyeX::uniform(uint8_t f[], int width, int height, uint8_t h[], int length)
{
	int l = width*height;
	int hist[256];
	for (int a=0; a<256; a++) {
		hist[a] = 0;
	}
	for (int k=0; k<l; k++) {
		hist[f[k]]++;
	}
	int maxH = 0;
	int maxV = hist[maxH];
	printf("%3d: %4d\n", 0, hist[0]);
	for (int a=1; a<256; a++) {
		int v = hist[a];
		if (v > maxV) {
			maxV = v;
			maxH = a;
		}
		printf("%3d: %4d\n", a, v);
	}
	assert(maxH < 255);
	int an = maxH-1, ap = maxH+1;
	int vn = hist[an], vp = hist[ap];
	float v = (float)(maxH*maxV + an*vn + ap*vp)/(maxV + vn + vp);
	printf("v = %f\n", v);
	
	for (int k=0; k<l; k++) {
		if (f[k] > 114) {
			h[k] = 255;
		}
		else {
			h[k] = 0;
		}
	}
	
	return true;
}
