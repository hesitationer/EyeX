 //
//  main.cpp
//  Keyboard
//
//  Created by SIFEN ZHONG on 30/9/2016.
//
//

#include "keyboard.hpp"
#include "keyboard_key.hpp"
#include "keyboard_0262.hpp"

int main(int argc, const char * argv[]) {
	
//	Mat f = imread(keyboard_folder + "DSC_0262.jpg", IMREAD_COLOR);
	
//	Mat g;
//	keyboard_frame(f, g);
//	imwrite(folder + "keyboard_0262_fra.png", g);

//	Mat g = imread(folder + "keyboard_0262_fra.png", IMREAD_COLOR);

//	Mat h;
//	keyboard_box(g, h);
//	imwrite(folder + "keyboard_0262_box.png", h);

	Mat h = imread(keyboard_folder + keyboard_name + keyboard_postfix, IMREAD_COLOR);
	Mat s;
	
	keyboard::key_box(keyH, h, s);
	imwrite(keyboard_folder + keyboard_name + "_H.png", s);

	Mat w;
	cvtColor(s, w, COLOR_BGR2GRAY);
	
	imshow("keyboard: w", w);
	waitKey();
	
	Mat r = w.clone();
	EyeX::uniform(w.ptr(), w.cols, w.rows, r.ptr(), 0);
	
	imshow("keyboard: r", r);
	waitKey(0);

//	imshow("keyboard: g", g);
//	waitKey();
	
//	imshow("keyboard: h", h);
//	waitKey();
	
    return 0;
}
