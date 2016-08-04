////============================================================================
//// Name        : OpenCV_Haar.cpp
//// Author      : haizhu
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
//#include <opencv2/opencv.hpp>
//
//using namespace cv;
////
////int main(int argc, char** argv) {
////	Mat image;
////	image = imread(argv[1], 1);
////	if (argc != 2 || !image.data) {
////		printf("No image data \n");
////		return -1;
////	}
////	namedWindow("Display Image", WINDOW_AUTOSIZE);
////	imshow("Display Image", image);
////	waitKey(0);
////	return 0;
////}
//#include <opencv2/opencv.hpp>
//#include <cstdio>
//#include <cstdlib>
//using namespace std;
//int main() {
//	// 加载Haar特征检测分类器
//	// OpenCV自带的分类器
//	const char *pstrCascadeFileName =
//			"/Users/haizhu/Downloads/openCV/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml";
//	CvHaarClassifierCascade *pHaarCascade = NULL;
//	pHaarCascade = (CvHaarClassifierCascade*) cvLoad(pstrCascadeFileName);
//
//	// 载入图像
//	const char *pstrImageName = "/Users/haizhu/Downloads/data/opencv/2.jpg";
//	IplImage *pSrcImage = cvLoadImage(pstrImageName, CV_LOAD_IMAGE_UNCHANGED);
//
//	IplImage *pGrayImage = cvCreateImage(cvGetSize(pSrcImage), IPL_DEPTH_8U, 1);
//	cvCvtColor(pSrcImage, pGrayImage, CV_BGR2GRAY);
//
//	// 人脸识别与标记
//	if (pHaarCascade != NULL) {
////		CvScalar FaceCirclecolors[8] = { { 0, 0, 0, 255 },	//
////				{   0, 128, 255 }, //
////				{ 0, 0, 255, 255 }, //
////				{ 0, 0, 255, 0 }, //
////				{ 0, 255, 128, 0 }, //
////				{ 0, 255, 255, 0 }, //
////				{ 0, 255, 0, 0 }, //
////				{ 0, 255, 0, 255 } };
//		CvScalar fontColor = cvScalar(128, 255, 0);
//
//		CvMemStorage *pcvMStorage = cvCreateMemStorage(0);
//		cvClearMemStorage(pcvMStorage);
//		// 识别人脸
////		DWORD dwTimeBegin, dwTimeEnd;
////		dwTimeBegin = GetTickCount();
//		CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage, pHaarCascade,
//				pcvMStorage);
////		dwTimeEnd = GetTickCount();
//
//		printf("人脸个数: %d  \n", pcvSeqFaces->total);
//
//		// 用圆圈标记人脸
//		for (int i = 0; i < pcvSeqFaces->total; i++) {
//			CvRect* r = (CvRect*) cvGetSeqElem(pcvSeqFaces, i);
//			CvPoint center;
//			int radius;
//			center.x = cvRound((r->x + r->width * 0.5));
//			center.y = cvRound((r->y + r->height * 0.5));
//			radius = cvRound((r->width + r->height) * 0.25);
//			cvCircle(pSrcImage, center, radius, fontColor, 2);
//		}
//		cvReleaseMemStorage(&pcvMStorage);
//	}
//
//	const char *pstrWindowsTitle = "人脸识别";
//	cvNamedWindow(pstrWindowsTitle, CV_WINDOW_AUTOSIZE);
//	cvShowImage(pstrWindowsTitle, pSrcImage);
//
//	cvWaitKey(0);
//
//	cvDestroyWindow(pstrWindowsTitle);
//	cvReleaseImage(&pSrcImage);
//	cvReleaseImage(&pGrayImage);
//	return 0;
//}
