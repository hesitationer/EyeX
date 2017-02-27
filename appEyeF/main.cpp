//
//  main.cpp
//  appEyeF
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace cv;

const float _A = PI2*135/2/360;

int main(int argc, const char * argv[])
{
	// parameters of YUV frames from capture
	int l1 = 1280;
	int l2 =  960;
	int l = l1*l2;
	float f_fov = _A;
	float f_pov = 0;
	
	// parameters of YUV frames for display
	int m1 = 1136;
	int m2 =  640;
	int n1 = 640;
	int n2 = 960;
	int m = m1*m2;
	float g_fov[] = {
		_A,
		PI*3/12,
		PI*3/12,
		PI/8,
		PI/8,
		PI/8,
		PI/8,
//		_A*2/8,
//		_A*2/8,
//		_A*3/4,
//		_A*2/3,
//		_A*2/3,
//		_A*2/3,
	};
	float g_pov[] = {
		0,
		0,
		PI*(+3)/12,
		PI*(-2.0F/16),
		PI*(+2.0F/16),
		PI*(+3.0F/16),
//		_A*(+1.0F/4),
//		_A*(-1.0F/4),
//		0,
//		_A*(+1.0F/3),
//		_A*(-1.0F/3),
	};
	int32_t (*map_k) = new int32_t[m];
	int16_t (*map_w)[4] = new int16_t[m][4];
	int32_t (*map_n) = new int32_t[m/4];
	int16_t (*map_z)[4] = new int16_t[m/4][4];
	
//	char name[80] = { "vlcsnap-2014-10-08-14h10m44s169" };
	char name[80] = { "vlcsnap-2014-10-08-14h11m15s224" };
//	char name[80] = { "vlcsnap-2014-10-08-14h09m24s135" };
	char ext[8] = { ".png" };
	
	std::string fname("/Users/zhongsifen/Data/zhuxin/");
	
	//int k=1;
	//if (k < argc) sscanf(argv[k++], "%s", folder);
	//if (k < argc) sscanf(argv[k++], "%s", name);
	//if (k < argc) sscanf(argv[k++], "%s", ext);
	//
	//char filename_inp[256];
	//char filename_out[256];
	//
	//sprintf(filename_inp, "%s%s%s", folder, name, ext);
	//sprintf(filename_out, "%s%s%s", folder, name, ".bmp");
	
	Mat f = imread(fname + name + ".png", IMREAD_COLOR);
	imshow("gamma: f", f);
	waitKey(0);
	
	l1 = f.cols;
	l2 = f.rows;
	Mat g = Mat(Size(m1, m2), f.type());
	Mat h = Mat(Size(n1, n2), f.type());
	
	std::string title("gamma");
	for (int view=0; view<1; view++)
	{
		EyeF_map_pov(l1, l2, f_fov, f_pov, m1, m2, g_fov[view], g_pov[view], map_k, map_w);
		EyeP_remap_w3(f.ptr(), f.cols, f.rows, g.ptr(), g.cols, g.rows, map_k, map_w);
		imshow(title + char(view), g);
		waitKey(0);
		
//		std::string pname = fname + "_fov_" + ('0' + view) + ".png";
//		imwrite(pname, g);
	}
	for (int view=1; view<6; view++)
	{
		EyeF_map_pov(l1, l2, f_fov, f_pov, n1, n2, g_fov[view], g_pov[view], map_k, map_w);
		EyeP_remap_w3(f.ptr(), f.cols, f.rows, h.ptr(), h.cols, h.rows, map_k, map_w);
		imshow(title + char(view), h );
		waitKey(0);
		
//		imwrite(fname + "_pov_" + ('0' + view) + ".png", g);
	}
	
	printf("Hello, world! This is gamma.\n");
	return 0;
}
