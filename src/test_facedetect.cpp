#include <iostream>

#include "facedetect.h"

string cascadeName =
//		"/data/opencv/waiopencv/opecv_data/cascade.xml";
		"/Users/haizhu/Documents/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_default.xml";

int main(int argc, const char** argv) {
	//	path = "/data/opencv/waiopencv/images/";
	//	saveFilePath = "/data/opencv/waiopencv/info.txt";
//	makeFacedetect(
//			"/Users/haizhu/Documents/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_default.xml",
//			"/data/opencv/waiopencv/images", "/data/opencv/waiopencv/info.txt");

	readFacedetect(cascadeName,
			"/data/opencv/waiopencv/images//24G5clcsl0Yrk_tbnqe1gg.jpeg");
//			"/Users/haizhu/Downloads/1.jpg");
	return 0;
}

