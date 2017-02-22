//
//  EyeP_g.cpp
//
//  Created by SIFEN ZHONG on 6/10/14.
//  Copyright (c) 2014 ___ZHONGSIFEN___. All rights reserved.
//

#include "_EyeP.hpp"
#include "EyeP_g.hpp"
#include "_opencv2.hpp"
using namespace cv;

void EyeP_g(float f_x, float f_y, float& g_x, float& g_y, void* param)
{
	float* a = (float*)param;
	float w = 1;

	g_x = f_x*a[0] + f_y*a[1] + a[2];
	g_y = f_x*a[3] + f_y*a[4] + a[5];
	w += f_x*a[6] + f_y*a[7];

	assert(fabsf(w) > 1e-8);
	w = 1.0F / w;
	g_x *= w;
	g_y *= w;
}

// f_x*a11 + f_y*a12 + b1 = g_x*w = g_x*(f_x*c1 + f_y*c2 + 1)
// f_x*a21 + f_y*a22 + b2 = g_y*w
// f_x*c1  + f_y*c2  + 1  = w

// degree == 8
// f_x*a11 + f_y*a12 + b1 - (f_x*g_x)*c1 - (f_y*g_x)*c2 = g_x
// f_x*a21 + f_y*a22 + b2 - (f_x*g_y)*c1 - (f_y*g_y)*c2 = g_y

// [a11 = a22 = 1]
// [a12 = a21 = 0]
// degree == 4
// f_x + b1 - (f_x*g_x)*c1 - (f_y*g_x)*c2 = g_x
// f_y + b2 - (f_x*g_y)*c1 - (f_y*g_y)*c2 = g_y
//
// fn_x + b1 - (fn_x*gn_x)*c1 - (fn_y*gn_x)*c2 = gn_x
// fn_y + b2 - (fn_x*gn_y)*c1 - (fn_y*gn_y)*c2 = gn_y
// fp_x + b1 - (fp_x*gp_x)*c1 - (fp_y*gp_x)*c2 = gp_x
// fp_y + b2 - (fp_x*gp_y)*c1 - (fp_y*gp_y)*c2 = gp_y
//
// [fn_y = gn_y = 0]
// b2 = 0
// degree == 3
// fn_x + b1 - (fn_x*gn_x)*c1                  = gn_x
// fp_x + b1 - (fp_x*gp_x)*c1 - (fp_y*gp_x)*c2 = gp_x
// fp_y      - (fp_x*gp_y)*c1 - (fp_y*gp_y)*c2 = gp_y
//
// [fp_y = gp_y = 0]
// c2 = 0
// degree == 2
// fn_x + b1 - (fn_x*gn_x)*c1 = gn_x
// fp_x + b1 - (fp_x*gp_x)*c1 = gp_x
//
// b1 - (fn_x*gn_x)*c1 = gn_x - fn_x
// b1 - (fp_x*gp_x)*c1 = gp_x - fp_x
//
// ((fp_x*gp_x)- (fn_x*gn_x))*c1 = (fp_x - gp_x) - (fn_x - gn_x)
//
// c = ((fp_x - gp_x) - (fn_x - gn_x)) / ((fp_x*gp_x)- (fn_x*gn_x))
// b = (fn_x*gn_x)*c - (fn_x-  gn_x)


// f_x*a + b1      - (f_x*g_x)*c1 = g_x
// f_y*a      + b2 - (f_x*g_y)*c1 = g_y

void _per_pt(double a0[], double a1[], double b0[], double b1[], float f[], float g[])
{
	a0[0] = a1[3] = f[0];
	a0[1] = a1[4] = f[1];
	a0[2] = a1[5] = 1;
	a0[3] = a0[4] = a0[5] =
	a1[0] = a1[1] = a1[2] = 0;
	a0[6] = -f[0] * g[0];
	a0[7] = -f[1] * g[0];
	a1[6] = -f[0] * g[1];
	a1[7] = -f[1] * g[1];
	b0[0] = g[0];
	b1[0] = g[1];
}

void _per_ln(double a0[], double a1[], double b0[], double b1[], float f[], float g[])
{
	a0[0] = a1[1] = g[0];
	a0[3] = a1[4] = g[1];
	a0[6] = a1[7] = 1;
	a0[1] = a0[4] = a0[7] =
	a1[0] = a1[3] = a1[6] = 0;
	a0[2] = -g[0] * f[0];
	a0[5] = -g[1] * f[0];
	a1[2] = -g[0] * f[1];
	a1[5] = -g[1] * f[1];
	b0[0] = f[0];
	b1[0] = f[1];
}

void EyeP_per_pt(const float pt_f[], const float pt_g[], int pt_count, float u[])
{
	float (*src)[2] = (float(*)[2])pt_f;
	float (*dst)[2] = (float(*)[2])pt_g;
	int n = pt_count * 2;
	double A_[8][8], B_[8], X_[8];
	Mat A(n, 8, CV_64F, A_), B(n, 1, CV_64F, B_);
	Mat X(8, 1, CV_64F, X_);
	double* x = X.ptr<double>();
	
	double **a = new double*[n];
	double **b = new double*[n];
	for (int k = 0; k<n; k++) {
		a[k] = A.ptr<double>(k);
		b[k] = B.ptr<double>(k);
	}
	
	for (int i = 0, k0 = 0, k1 = 1; i<pt_count; i++, k0 += 2, k1 += 2) {
		_per_pt(a[k0], a[k1], b[k0], b[k1], src[i], dst[i]);
	}
	
	solve(A.t()*A, A.t()*B, X, DECOMP_SVD);
	
	for (int j = 0; j<8; j++) {
		u[j] = (float)x[j];
	}
}

void EyeP_per_ln(const float ln_f[], const float ln_g[], int ln_count, float u[])
{
	float (*f)[2] = (float(*)[2])ln_f;
	float (*g)[2] = (float(*)[2])ln_g;
	int l = ln_count * 2;
	Mat A(l, 8, CV_64F), B(l, 1, CV_64F);
	Mat X(8, 1, CV_64F);
	double* x = X.ptr<double>();
	
	double **a = new double*[l];
	double **b = new double*[l];
	for (int k = 0; k<l; k++) {
		a[k] = A.ptr<double>(k);
		b[k] = B.ptr<double>(k);
	}
	
	for (int i = 0, k0 = 0, k1 = 1; i<ln_count; i++, k0 += 2, k1 += 2) {
		_per_ln(a[k0], a[k1], b[k0], b[k1], f[i], g[i]);
	}
	
	solve(A.t()*A, A.t()*B, X, DECOMP_SVD);

	for (int j = 0; j<8; j++) {
		u[j] = (float)x[j];
	}
}

void EyeP_per_pt_ln(const float pt_f[], const float pt_g[], int pt_count, const float ln_f[], const float ln_g[], const int ln_count, float u[])
{
	int count = pt_count + ln_count;
	int l = count * 2;
	Mat A(l, 8, CV_64F), B(l, 1, CV_64F);
	Mat X(8, 1, CV_64F);
	double **a = new double*[l];
	double **b = new double*[l];
	for (int k = 0; k<l; k++) {
		a[k] = A.ptr<double>(k);
		b[k] = B.ptr<double>(k);
	}
	double* x = X.ptr<double>();
	
	float (*f)[2] = (float(*)[2])pt_f;
	float (*g)[2] = (float(*)[2])pt_g;
	int k0 = 0, k1 = 1;
	for (int i=0; i<pt_count; i++, k0 += 2, k1 += 2) {
		_per_pt(a[k0], a[k1], b[k0], b[k1], f[i], g[i]);
	}
	f = (float(*)[2])ln_f;
	g = (float(*)[2])ln_g;
	for (int i=0; i<ln_count; i++, k0 += 2, k1 += 2) {
		_per_ln(a[k0], a[k1], b[k0], b[k1], f[i], g[i]);
	}
	
	solve(A.t()*A, A.t()*B, X, DECOMP_SVD);
	
	for (int j = 0; j<8; j++) {
		u[j] = (float)x[j];
		printf("u = %f\n", u[j]);
	}
}

void EyeP_pt_ln(Point2f& pt_1, Point2f& pt_2, Point2f& ln)
{
	double _a[4], _b[2], _x[2];
	Mat a(Size(2, 2), CV_64F, _a);
	Mat b(Size(1, 2), CV_64F, _b);
	Mat x(Size(1, 2), CV_64F, _x);
	_a[0] = pt_1.x;
	_a[1] = pt_1.y;
	_a[2] = pt_2.x;
	_a[3] = pt_2.y;
	_b[0] = -1.0;
	_b[1] = -1.0;
	solve(a, b, x);
	ln.x = (float)_x[0];
	ln.y = (float)_x[1];
}

#if 0
Mat getPerTransform(
					const Point2f pt_src[], const Point2f pt_dst[], int pt_count)
{
	int l = pt_count * 2;
	Mat M(3, 3, CV_64F), X(8, 1, CV_64F, M.data);
	Mat A(l, 8, CV_64F), B(l, 1, CV_64F);
	
	double **a = new double*[l];
	double **b = new double*[l];
	for (int k = 0; k<l; k++)
	{
		a[k] = A.ptr<double>(k);
		b[k] = B.ptr<double>(k);
	}
	
	for (int i = 0, k0 = 0, k1 = 1; i<pt_count; i++, k0 += 2, k1 += 2)
	{
		a[k0][0] = a[k1][3] = pt_src[i].x;
		a[k0][1] = a[k1][4] = pt_src[i].y;
		a[k0][2] = a[k1][5] = 1;
		a[k0][3] = a[k0][4] = a[k0][5] =
		a[k1][0] = a[k1][1] = a[k1][2] = 0;
		a[k0][6] = -pt_src[i].x * pt_dst[i].x;
		a[k0][7] = -pt_src[i].y * pt_dst[i].x;
		a[k1][6] = -pt_src[i].x * pt_dst[i].y;
		a[k1][7] = -pt_src[i].y * pt_dst[i].y;
		b[k0][0] = pt_dst[i].x;
		b[k1][0] = pt_dst[i].y;
	}
	
	solve(A.t()*A, A.t()*B, X, DECOMP_SVD);
	((double*)M.data)[8] = 1.;
	
	return M;
}

/* Calculates coefficients of perspective transformation
 * which maps (xi,yi) to (ui,vi), (i=1,2,3,4):
 *
 *      c00*xi + c01*yi + c02
 * ui = ---------------------
 *      c20*xi + c21*yi + c22
 *
 *      c10*xi + c11*yi + c12
 * vi = ---------------------
 *      c20*xi + c21*yi + c22
 *
 * Coefficients are calculated by solving linear system:
 * / x0 y0  1  0  0  0 -x0*u0 -y0*u0 \ /c00\ /u0\
 * | x1 y1  1  0  0  0 -x1*u1 -y1*u1 | |c01| |u1|
 * | x2 y2  1  0  0  0 -x2*u2 -y2*u2 | |c02| |u2|
 * | x3 y3  1  0  0  0 -x3*u3 -y3*u3 |.|c10|=|u3|,
 * |  0  0  0 x0 y0  1 -x0*v0 -y0*v0 | |c11| |v0|
 * |  0  0  0 x1 y1  1 -x1*v1 -y1*v1 | |c12| |v1|
 * |  0  0  0 x2 y2  1 -x2*v2 -y2*v2 | |c20| |v2|
 * \  0  0  0 x3 y3  1 -x3*v3 -y3*v3 / \c21/ \v3/
 *
 * where:
 *   cij - matrix coefficients, c22 = 1
 */
cv::Mat cv::getPerspectiveTransform( const Point2f src[], const Point2f dst[] )
{
	Mat M(3, 3, CV_64F), X(8, 1, CV_64F, M.data);
	double a[8][8], b[8];
	Mat A(8, 8, CV_64F, a), B(8, 1, CV_64F, b);
	
	for( int i = 0; i < 4; ++i )
	{
		a[i][0] = a[i+4][3] = src[i].x;
		a[i][1] = a[i+4][4] = src[i].y;
		a[i][2] = a[i+4][5] = 1;
		a[i][3] = a[i][4] = a[i][5] =
		a[i+4][0] = a[i+4][1] = a[i+4][2] = 0;
		a[i][6] = -src[i].x*dst[i].x;
		a[i][7] = -src[i].y*dst[i].x;
		a[i+4][6] = -src[i].x*dst[i].y;
		a[i+4][7] = -src[i].y*dst[i].y;
		b[i] = dst[i].x;
		b[i+4] = dst[i].y;
	}
	
	solve( A, B, X, DECOMP_SVD );
	((double*)M.data)[8] = 1.;
	
	return M;
}

/* Calculates coefficients of affine transformation
 * which maps (xi,yi) to (ui,vi), (i=1,2,3):
 *
 * ui = c00*xi + c01*yi + c02
 *
 * vi = c10*xi + c11*yi + c12
 *
 * Coefficients are calculated by solving linear system:
 * / x0 y0  1  0  0  0 \ /c00\ /u0\
 * | x1 y1  1  0  0  0 | |c01| |u1|
 * | x2 y2  1  0  0  0 | |c02| |u2|
 * |  0  0  0 x0 y0  1 | |c10| |v0|
 * |  0  0  0 x1 y1  1 | |c11| |v1|
 * \  0  0  0 x2 y2  1 / |c12| |v2|
 *
 * where:
 *   cij - matrix coefficients
 */

cv::Mat cv::getAffineTransform( const Point2f src[], const Point2f dst[] )
{
	Mat M(2, 3, CV_64F), X(6, 1, CV_64F, M.data);
	double a[6*6], b[6];
	Mat A(6, 6, CV_64F, a), B(6, 1, CV_64F, b);
	
	for( int i = 0; i < 3; i++ )
	{
		int j = i*12;
		int k = i*12+6;
		a[j] = a[k+3] = src[i].x;
		a[j+1] = a[k+4] = src[i].y;
		a[j+2] = a[k+5] = 1;
		a[j+3] = a[j+4] = a[j+5] = 0;
		a[k] = a[k+1] = a[k+2] = 0;
		b[i*2] = dst[i].x;
		b[i*2+1] = dst[i].y;
	}
	
	solve( A, B, X );
	return M;
}

void cv::invertAffineTransform(InputArray _matM, OutputArray __iM)
{
	Mat matM = _matM.getMat();
	CV_Assert(matM.rows == 2 && matM.cols == 3);
	__iM.create(2, 3, matM.type());
	Mat _iM = __iM.getMat();
	
	if( matM.type() == CV_32F )
	{
		const float* M = (const float*)matM.data;
		float* iM = (float*)_iM.data;
		int step = (int)(matM.step/sizeof(M[0])), istep = (int)(_iM.step/sizeof(iM[0]));
		
		double D = M[0]*M[step+1] - M[1]*M[step];
		D = D != 0 ? 1./D : 0;
		double A11 = M[step+1]*D, A22 = M[0]*D, A12 = -M[1]*D, A21 = -M[step]*D;
		double b1 = -A11*M[2] - A12*M[step+2];
		double b2 = -A21*M[2] - A22*M[step+2];
		
		iM[0] = (float)A11; iM[1] = (float)A12; iM[2] = (float)b1;
		iM[istep] = (float)A21; iM[istep+1] = (float)A22; iM[istep+2] = (float)b2;
	}
	else if( matM.type() == CV_64F )
	{
		const double* M = (const double*)matM.data;
		double* iM = (double*)_iM.data;
		int step = (int)(matM.step/sizeof(M[0])), istep = (int)(_iM.step/sizeof(iM[0]));
		
		double D = M[0]*M[step+1] - M[1]*M[step];
		D = D != 0 ? 1./D : 0;
		double A11 = M[step+1]*D, A22 = M[0]*D, A12 = -M[1]*D, A21 = -M[step]*D;
		double b1 = -A11*M[2] - A12*M[step+2];
		double b2 = -A21*M[2] - A22*M[step+2];
		
		iM[0] = A11; iM[1] = A12; iM[2] = b1;
		iM[istep] = A21; iM[istep+1] = A22; iM[istep+2] = b2;
	}
	else
		CV_Error( CV_StsUnsupportedFormat, "" );
}

cv::Mat cv::getPerspectiveTransform(InputArray _src, InputArray _dst)
{
	Mat src = _src.getMat(), dst = _dst.getMat();
	CV_Assert(src.checkVector(2, CV_32F) == 4 && dst.checkVector(2, CV_32F) == 4);
	return getPerspectiveTransform((const Point2f*)src.data, (const Point2f*)dst.data);
}

cv::Mat cv::getAffineTransform(InputArray _src, InputArray _dst)
{
	Mat src = _src.getMat(), dst = _dst.getMat();
	CV_Assert(src.checkVector(2, CV_32F) == 3 && dst.checkVector(2, CV_32F) == 3);
	return getAffineTransform((const Point2f*)src.data, (const Point2f*)dst.data);
}
#endif
