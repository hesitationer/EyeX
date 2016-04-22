//
//  EyeT.hpp
//  EyeX
//
//  Created by SIFEN ZHONG on 23/10/15.
//
//

#ifndef EyeT_hpp
#define EyeT_hpp

#include "EyeX.hpp"

typedef void TransformApp(
						  cv::InputArray src, cv::OutputArray dst,
						  cv::InputArray M, cv::Size dsize,
						  int flags,						// =INTER_LINEAR,
						  int borderMode,					// =BORDER_CONSTANT,
						  const cv::Scalar& borderValue		// =Scalar()
						  )
;
typedef cv::Mat TransformGet(
							 const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count
							 )
;

class EyeT {
public:
	enum TransformType {
		TRANSFORM_IDE,
		TRANSFORM_TRA,
		TRANSFORM_SIM,
		TRANSFORM_AFF,
		TRANSFORM_PER,
	};

protected:
	TransformType type;
	TransformApp* app;
	TransformGet* get;

public:
	void setType(TransformType type);
	cv::Mat getTransform(cv::Point2f pt_src[], cv::Point2f pt_dst[], int pt_count);
	void appTransform(cv::InputArray src, cv::OutputArray dst, cv::InputArray op);

//	int transform_set_pt_nrm(void* p,
//							 cv::Point2f pt_src[]);
	
	static cv::Mat getTransformIde(
								   const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count);
	
	static cv::Mat getTransformTra(
								   const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count);
	
	static cv::Mat getTransformSim(
								   const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count);
	
	static cv::Mat getTransformAff(
								   const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count);
	
	static cv::Mat getTransformPer(
								   const cv::Point2f pt_src[], const cv::Point2f pt_dst[], int pt_count);
};

#endif /* EyeT_hpp */
