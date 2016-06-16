//
//  main.cpp
//  appEyeF
//
//  Created by SIFEN ZHONG on 24/8/15.
//
//

#include "F135/F135.hpp"
#include "EyeF/EyeF.hpp"
#include "EyeP/EyeP.hpp"
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace cv;

int main(int argc, const char * argv[])
{
	//char name[80] = { "vlcsnap-2014-10-08-14h10m44s169" };
	char name[80] = { "vlcsnap-2014-10-08-14h11m15s224" };
	//char name[80] = { "vlcsnap-2014-10-08-14h09m24s135" };
	char ext[8] = { ".png" };
	
	std::string fname("/Users/zhongsifen/Data/zhuxin/");
	
	Mat f = imread(fname + name + ".png", IMREAD_COLOR);
	imshow("input: f", f);
	waitKey(0);
	
	Mat g = Mat(Size(f135::n_x, f135::n_y), f.type());
	Mat a = Mat(Size(f135::l_x, f135::l_y), f.type());
	
	std::string title("fisheye");

	F135_init();
	F135_fg(f, g);

	imshow("F135: g", g);
	imshow("F135: a", a);

	waitKey(0);

	printf("Hello, world! This is gamma.\n");
	return 0;
}
