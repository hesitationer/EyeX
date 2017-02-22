// transform.h

#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_ 1

#include "_opencv2.hpp"

#define TRANSFORM_TRA 1
#define TRANSFORM_SIM 2
#define TRANSFORM_AFF 3
#define TRANSFORM_PER 4

void* transform_new()
;
void transform_delete(void* p)
;
int transform_set_type(void* p,
		int type)
;
int transform_set_pt(void* p,
	cv::Point2f pt_src[],
	cv::Point2f pt_dst[],
	int pt_count)
;
int transform_set_pt_nrm(void* p,
	cv::Point2f pt_src[])
;
int transform_get(void* p)
;
int transform_app(void* p,
	cv::InputArray src, cv::OutputArray dst)
;

cv::Mat getTraTransform(
	const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count)
;
cv::Mat getSimTransform(
	const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count)
;
cv::Mat getAffTransform(
	const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count)
;
cv::Mat getPerTransform(
	const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count)
;

cv::Mat getPerTransform(const cv::Point2f f[], const cv::Point2f g[])
;
bool appPerTransform(cv::Mat& M, cv::Point2f f[], cv::Point2f g[], int count)
;

bool getPerTransform(const cv::Point2f f[], const cv::Point2f g[], void* p)
;
bool appPerTransform(float f_x, float f_y, float& g_x, float& g_y, void* p)
;

#endif // _TRANSFORM_H_
