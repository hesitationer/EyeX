//
//  EyeP_g.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 23/8/15.
//
//

#ifndef EyeX_EyeP_g_hpp
#define EyeX_EyeP_g_hpp

#include "EyeP.hpp"

void EyeP_g(float f_x, float f_y, float& g_x, float& g_y, void* param)
;
void EyeP_per_pt(const float pt_f[], const float pt_g[], int pt_count, float u[])
;
void EyeP_per_ln(const float ln_f[], const float ln_g[], int pt_count, float u[])
;
void EyeP_per_pt_ln(const float pt_f[], const float pt_g[], int pt_count, const float ln_f[], const float ln_g[], const int ln_count, float u[])
;

void EyeP_pt_ln(Point2f& pt_1, Point2f& pt_2, Point2f& ln)
;

#endif
