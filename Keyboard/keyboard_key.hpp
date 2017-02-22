//
//  keyboard_key.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 9/10/2016.
//
//

#ifndef keyboard_key_hpp
#define keyboard_key_hpp

#include "keyboard.hpp"

typedef struct {
	int x, y;
	int width, height;
}
Key;

const Key keyH = { 1290, 574, 40, 40, };

namespace keyboard {
	bool key_box(const Key& key, Mat& f, Mat& box);
}

#endif /* keyboard_key_hpp */
