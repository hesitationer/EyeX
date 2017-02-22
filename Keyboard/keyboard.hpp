//
//  keyboard.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 1/10/2016.
//
//

#ifndef keyboard_hpp
#define keyboard_hpp

#include "EyeM/EyeM.hpp"
#include "EyeP/EyeP.hpp"
#include "EyeP/EyeP_g.hpp"
#include "_opencv2.hpp"
using namespace cv;

typedef struct {
	Point2f* point_f;
	Point2f* point_g;
	
	Point2f* point_box;
}
Keyboard;

extern Keyboard _keyboard;

const Size2f _size(4000, 1500);
const float _margin = 16;

bool keyboard_frame(Mat& f, Mat& g, Keyboard& keyboard = _keyboard);
bool keyboard_box(Mat& f, Mat& g, Keyboard& keyboard = _keyboard);

#endif /* keyboard_hpp */
