#include <iostream>

#include "facedetect.h"
#include "LBPH_face_recognizer.h"

string cascadeName =
//		"/data/opencv/waiopencv/opecv_data/cascade.xml";
		"/Users/haizhu/Documents/tools/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_default.xml";
//
int main(int argc, const char** argv) {

	string output_file = "/data/opencv/waiopencv/result.txt";
	string fn_csv = "/data/opencv/waiopencv/csv.csv";
	train(fn_csv, output_file);

	readFacedetect(cascadeName,
//			"/Users/haizhu/Downloads/data/opencv/CM_KSQBAOHED8s41TXBPxw.jpeg@200w_200h_75q.jpeg",
			"/Users/haizhu/Downloads/data/opencv/waiopencv/images/ZdcGtHqm7cwrk_tbnqe1gg.jpeg",
//			"/Users/haizhu/Downloads/1.jpg",
			output_file);

	return 0;
}
