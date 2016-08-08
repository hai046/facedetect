#include <iostream>

#include "facedetect.h"

string cascadeName =
//		"/data/opencv/waiopencv/opecv_data/cascade.xml";
		"/Users/haizhu/Documents/tools/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_default.xml";

int main(int argc, const char** argv) {
	//	path = "/data/opencv/waiopencv/images/";
	//	saveFilePath = "/data/opencv/waiopencv/info.txt";
//	makeFacedetect(
//			"/Users/haizhu/Documents/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_default.xml",
//			"/data/opencv/waiopencv/images", "/data/opencv/waiopencv/info.txt");

	readFacedetect(cascadeName,
			"/data/opencv/waiopencv/images//24G5clcsl0Yrk_tbnqe1gg.jpeg",
//			"/Users/haizhu/Downloads/1.jpg",
			"/data/opencv/waiopencv/result.txt");

	//	string fn_csv = "/data/opencv/waiopencv/csv.csv";	//string(argv[1]);
	////
	////	// Get the output file name and path
	//	string output_file = "/data/opencv/waiopencv/result.txt";// string(argv[2]);
	//	train(fn_csv, output_file);
	//
	//	cout << endl;
	//	cout << endl;
	//
	//	int user =
	//			recognize_user(output_file,
	//					"/Users/haizhu/Downloads/data/opencv/waiopencv/zhaosihan/XveZkfH4ldID8s41TXBPxw.jpeg@200w_200h_75q.jpeg");
	//	cout << "user:" << user << endl;

	return 0;
}

