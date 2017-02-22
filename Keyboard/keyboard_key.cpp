//
//  keyboard_key.cpp
//  EyeX
//
//  Created by SIFEN ZHONG on 9/10/2016.
//
//

#include "keyboard_key.hpp"
using namespace keyboard;

bool keyboard::key_box(const Key& key, Mat& f, Mat& box)
{
	Rect r(key.x-key.width/2, key.y-key.height/2, key.width, key.height);
	box = f(r);

	return true;
}
