#include "facedetect.h"
#include "LBPH_face_recognizer.h"
//string cascadeName =
//		"/Users/haizhu/Documents/opencv-2.4.13/data/haarcascades/haarcascade_frontalface_default.xml";
//string nestedCascadeName =
//		"/Users/haizhu/Documents/opencv-2.4.13/data/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
//

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
int makeFacedetect(string cascadeName, string path, string saveFilePath) {
//	path = "/data/opencv/waiopencv/images/";
//	saveFilePath = "/data/opencv/waiopencv/info.txt";

	bool tryflip = true;
	double scale = 1;

	vector<string> files = scanFile(path);

	bool showImage = files.size() == 1;

	ofstream saveInfoFile(saveFilePath, ios::out);

	for (int i = 0; i < files.size(); i++) {
		CvCapture* capture = 0;
		Mat frame, frameCopy, image;
		string inputName;

		CascadeClassifier cascade, nestedCascade;

		inputName = files[i];
		if (!cascade.load(cascadeName)) {
			cerr << "ERROR: Could not load classifier cascade" << endl;
			return -1;
		}

		image = imread(inputName, 1);
		if (image.empty()) {
			capture = cvCaptureFromAVI(inputName.c_str());
			if (!capture)
				cout << "Capture from AVI didn't work" << endl;
		}

		if (showImage) {
			cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
		}
		cout << "In image read:" << endl;
		string name = inputName;

//				inputName.substr(inputName.find_last_of("/") + 1,
//				inputName.length());

		string result = detectFaceAndDraw(showImage, name, image, cascade,
				nestedCascade, scale, tryflip);

		if (result.length() > 0) {
			saveInfoFile << result << endl;
		}

		cout << "result:" << result << endl;
		if (showImage) {
			waitKey(0);
		}
		if (showImage) {
			cvDestroyWindow("result");
		}
	}
	saveInfoFile.close();

	return 0;
}

vector<string> scanFile(string dirPath) {
	vector<string> files;
	DIR *dir = NULL;
	if ((dir = opendir(dirPath.data())) == NULL) {

		files.push_back(dirPath);
		return files;
	}

	struct dirent *ptr = NULL;
	while ((ptr = readdir(dir)) != NULL) {
		if (ptr->d_name[0] != '.') { //除去根文件目录
//			strcpy(file_path, path);
//			if (path[strlen(path) - 1] != '/')
//				strcat(file_path, "/");
			stringstream fileStream;
			fileStream << dirPath << "/" << ptr->d_name;
//			cout << fileStream.str() << endl;
			files.push_back(fileStream.str());
		}
	}
	return files;

}

string detectFaceAndDraw(bool showImage, string name, Mat& img,
		CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
		double scale, bool tryflip, string model_path) {
	stringstream result_stream;
	int i = 0;
	double t = 0;
	vector<Rect> faces, faces2;
	const static Scalar colors[] = { CV_RGB(0, 0, 255), CV_RGB(0, 128, 255),
			CV_RGB(0, 255, 255), CV_RGB(0, 255, 0), CV_RGB(255, 128, 0), CV_RGB(
					255, 255, 0), CV_RGB(255, 0, 0), CV_RGB(255, 0, 255) };
	Mat gray, smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale),
	CV_8UC1);

	cvtColor(img, gray, COLOR_BGR2GRAY);
	resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
	equalizeHist(smallImg, smallImg);

	t = (double) cvGetTickCount();

	cascade.detectMultiScale(smallImg, faces, 1.1, 2, 0
	//|CASCADE_FIND_BIGGEST_OBJECT
	//|CASCADE_DO_ROUGH_SEARCH
			| CASCADE_SCALE_IMAGE, Size(30, 30));
	if (tryflip) {
		flip(smallImg, smallImg, 1);
		cascade.detectMultiScale(smallImg, faces2, 1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
				| CASCADE_SCALE_IMAGE, Size(30, 30));
		for (vector<Rect>::const_iterator r = faces2.begin(); r != faces2.end();
				r++) {
			faces.push_back(
					Rect(smallImg.cols - r->x - r->width, r->y, r->width,
							r->height));
		}
	}
	t = (double) cvGetTickCount() - t;
	printf("detection time = %g ms\n",
			t / ((double) cvGetTickFrequency() * 1000.));
	Ptr<LBPHFaceRecognizer> model;
	if (faces.size() > 0) {
		result_stream << name << " " << faces.size();
	}

	cout << " model_path=" << model_path << endl;
	model = createLBPHFaceRecognizer();
	model->load(model_path);
	cout << "  Threshold=" << model->getThreshold() << endl;
//	model->setThreshold(0.0);

	for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end();
			r++, i++) {
		Mat smallImgROI;
		vector<Rect> nestedObjects;
		Point center;
		Scalar color = colors[i % 8];
		int radius;

//		double aspect_ratio = (double) r->width / r->height;
//		if (0.75 < aspect_ratio && aspect_ratio < 1.3) {
		center.x = cvRound((r->x + r->width * 0.5) * scale);
		center.y = cvRound((r->y + r->height * 0.5) * scale);
//			radius = cvRound((r->width + r->height) * 0.25 * scale);
//			circle(img, center, radius, color, 3, 8, 0);
//
//			char text[12];
//			gcvt(i, 12, text);
//			putText(img, String(text), center, 1, 1, color);
//
//		} else

		result_stream << " " << r->x << " " << r->y << " "
				<< r->x + r->width - 1 << " " << r->y + r->height - 1;

		rectangle(img, cvPoint(cvRound(r->x * scale), cvRound(r->y * scale)),
				cvPoint(cvRound((r->x + r->width - 1) * scale),
						cvRound((r->y + r->height - 1) * scale)), color, 3, 8,
				0);

		{
			Mat face = smallImg(*r);
//			//在这里直接转换成LBP
			Mat lbp_face = Mat::zeros(face.size(), face.type());
			olbp_<uchar>(face, lbp_face);
			int user = recognize_user(model, lbp_face);
			stringstream textstream;

//			imwrite(
//					"/Users/haizhu/Downloads/data/opencv/waiopencv/crop_face.jpg",
//					face);
//			imwrite(
//					"/Users/haizhu/Downloads/data/opencv/waiopencv/crop_lbp_face.jpg",
//					lbp_face);

			center.x = cvRound((r->x + r->width * 0.5) * scale);
			center.y = cvRound((r->y + r->height * 0.5) * scale);
			textstream << "" << user;
			putText(img, textstream.str(), center, 1, 1, color);
		}

		if (nestedCascade.empty())
			continue;
		smallImgROI = smallImg(*r);

		nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2, 0
		//|CASCADE_FIND_BIGGEST_OBJECT
		//|CASCADE_DO_ROUGH_SEARCH
		//|CASCADE_DO_CANNY_PRUNING
				| CASCADE_SCALE_IMAGE, Size(30, 30));

		for (vector<Rect>::const_iterator nr = nestedObjects.begin();
				nr != nestedObjects.end(); nr++) {
			center.x = cvRound((r->x + nr->x + nr->width * 0.5) * scale);
			center.y = cvRound((r->y + nr->y + nr->height * 0.5) * scale);
			radius = cvRound((nr->width + nr->height) * 0.25 * scale);
			circle(img, center, radius, color, 3, 8, 0);
		}

	}

	if (showImage) {
		cv::imshow("result", img);
	}
	return result_stream.str();
}

int readFacedetect(string cascadeName, string inputName, string model_path) {

	bool tryflip = false;
	double scale = 1;

	bool showImage = true;
	CvCapture* capture = 0;
	Mat frame, frameCopy, image;

	CascadeClassifier cascade, nestedCascade;

	if (!cascade.load(cascadeName)) {
		cerr << "ERROR: Could not load classifier cascade" << endl;
		return -1;
	}

	image = imread(inputName, 1);
	if (image.empty()) {
		capture = cvCaptureFromAVI(inputName.c_str());
		if (!capture)
			cout << "Capture from AVI didn't work" << endl;
	}

	if (showImage) {
		cvNamedWindow("result", CV_WINDOW_AUTOSIZE);
	}
	cout << "In image read:" << endl;

	string result = detectFaceAndDraw(showImage, inputName, image, cascade,
			nestedCascade, scale, tryflip, model_path);

	cout << "result:" << result << endl;
	if (showImage) {
		waitKey(0);
	}
	if (showImage) {
		cvDestroyWindow("result");
	}

	return 0;
}

