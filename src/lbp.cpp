#include "lbp.h"

//opencv 2.0以后版本的LBP算法
template<typename _Tp> static
void olbp_(InputArray _src, OutputArray _dst) {
	// get matrices
	Mat src = _src.getMat();
	// allocate memory for result
	_dst.create(src.rows - 2, src.cols - 2, CV_8UC1);
	Mat dst = _dst.getMat();
	// zero the result matrix
	dst.setTo(0);
	// calculate patterns
	for (int i = 1; i < src.rows - 1; i++) {
		for (int j = 1; j < src.cols - 1; j++) {
			_Tp center = src.at<_Tp>(i, j);
			unsigned char code = 0;
			code |= (src.at<_Tp>(i - 1, j - 1) >= center) << 7;
			code |= (src.at<_Tp>(i - 1, j) >= center) << 6;
			code |= (src.at<_Tp>(i - 1, j + 1) >= center) << 5;
			code |= (src.at<_Tp>(i, j + 1) >= center) << 4;
			code |= (src.at<_Tp>(i + 1, j + 1) >= center) << 3;
			code |= (src.at<_Tp>(i + 1, j) >= center) << 2;
			code |= (src.at<_Tp>(i + 1, j - 1) >= center) << 1;
			code |= (src.at<_Tp>(i, j - 1) >= center) << 0;
			dst.at<unsigned char>(i - 1, j - 1) = code;
		}
	}
}
//
////基于旧版本的opencv的LBP算法opencv1.0
//void LBP(IplImage *src, IplImage *dst) {
//	int tmp[8] = { 0 };
//	CvScalar s;
//
//	IplImage * temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	uchar *data = (uchar*) src->imageData;
//	int step = src->widthStep;
//
//	cout << "step" << step << endl;
//
//	for (int i = 1; i < src->height - 1; i++)
//		for (int j = 1; j < src->width - 1; j++) {
//			int sum = 0;
//			if (data[(i - 1) * step + j - 1] >= data[i * step + j])
//				tmp[0] = 1;
//			else
//				tmp[0] = 0;
//			if (data[i * step + (j - 1)] >= data[i * step + j])
//				tmp[1] = 1;
//			else
//				tmp[1] = 0;
//			if (data[(i + 1) * step + (j - 1)] >= data[i * step + j])
//				tmp[2] = 1;
//			else
//				tmp[2] = 0;
//			if (data[(i + 1) * step + j] >= data[i * step + j])
//				tmp[3] = 1;
//			else
//				tmp[3] = 0;
//			if (data[(i + 1) * step + (j + 1)] >= data[i * step + j])
//				tmp[4] = 1;
//			else
//				tmp[4] = 0;
//			if (data[i * step + (j + 1)] >= data[i * step + j])
//				tmp[5] = 1;
//			else
//				tmp[5] = 0;
//			if (data[(i - 1) * step + (j + 1)] >= data[i * step + j])
//				tmp[6] = 1;
//			else
//				tmp[6] = 0;
//			if (data[(i - 1) * step + j] >= data[i * step + j])
//				tmp[7] = 1;
//			else
//				tmp[7] = 0;
//			//计算LBP编码
//			s.val[0] = (tmp[0] * 1 + tmp[1] * 2 + tmp[2] * 4 + tmp[3] * 8
//					+ tmp[4] * 16 + tmp[5] * 32 + tmp[6] * 64 + tmp[7] * 128);
//
//			cvSet2D(dst, i, j, s); //写入LBP图像
//		}
//}
//
//int main(int argc, const char** argv) {
//	IplImage* face =
//			cvLoadImage(
//					"/Users/haizhu/Downloads/data/opencv/waiopencv/images/__y28HCrraUrk_tbnqe1gg.jpeg",
//					CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
//
////	IplImage* Gray_face = cvCreateImage(cvSize(face->width, face->height),
////			face->depth, 1); //先分配图像空间
////	cvCvtColor(face, Gray_face, CV_BGR2GRAY); //把载入图像转换为灰度图
////	IplImage* lbp_face = cvCreateImage(cvGetSize(Gray_face), IPL_DEPTH_8U, 1); //先分配图像空间
//
////	cvNamedWindow("Gray Image", 1);
////	cvShowImage("Gray Image", Gray_face);
//
//	Mat face2 =
//			imread(
//					"/Users/haizhu/Downloads/data/opencv/waiopencv/images/__y28HCrraUrk_tbnqe1gg.jpeg",
//					0);
//
//	Mat lbp_face2 = Mat::zeros(face2.size(), face2.type());
//
//	//显示原始的输入图像
//	cvNamedWindow("Src Image", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Src Image", face);
//	//imshow("Src Image",face);
//
//	//计算输入图像的LBP纹理特征
////	LBP(Gray_face, lbp_face);
//	//olbp_<uchar>((Mat)face,(Mat)lbp_face);//有问题的调用
//	olbp_<uchar>(face2, lbp_face2);
//
//	//显示第一幅图像的LBP纹理特征图
////	cvNamedWindow("LBP Image", CV_WINDOW_AUTOSIZE);
////	cvShowImage("LBP Image", lbp_face);
//	//显示第二幅图 的LBP纹理特征图-一张yaleface人脸库中的人脸LBP特征图
//	namedWindow("LBP Image2", 1);
//	imshow("LBP Image2", lbp_face2);
//	waitKey();
//
//	//cvReleaseImage(&face);
//	cvDestroyWindow("Src Image");
//}
