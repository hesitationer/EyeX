//
//  main.cpp
//  fisheye
//
//  Created by SIFEN ZHONG on 29/10/2016.
//
//

#include "EyeX.hpp"
using namespace cv;

#include "fisheye_180.hpp"

int main(int argc, const char * argv[]) {
	bool ret = false;
	char key = '\0';
	
	VideoCapture cap(fisheye_folder + fisheye_name + fisheye_postfix);
	if (!cap.isOpened()) return -1;
 
	int width  = cap.get(CV_CAP_PROP_FRAME_WIDTH);
	int height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	
	Mat f;
	
	do {
		ret = cap.read(f);		if (!ret) break;
		imshow("fisheye: f", f);
		key = waitKey();
	} while (key != 'q');
	
    return 0;
}
