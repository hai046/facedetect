#include "LBPH_face_recognizer.h"
//#include "lbp.h"

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

static void read_csv(const string& filename, vector<Mat>& images,
		vector<int>& labels, char separator = ',') {
	std::ifstream file(filename.c_str(), ifstream::in);
	if (!file) {
		string error_message =
				"No valid input file was given, please check the given filename.";
		CV_Error(Error::StsBadArg, error_message);
	}
	string line, path, classlabel;
	while (getline(file, line)) {
		stringstream liness(line);
		getline(liness, path, separator);
		getline(liness, classlabel);
		if (!path.empty() && !classlabel.empty()) {
//				IplImage* Gray_face = cvCreateImage(cvSize(face->width, face->height),
//						face->depth, 1); //先分配图像空间
//				cvCvtColor(face, Gray_face, CV_BGR2GRAY); //把载入图像转换为灰度图
//				IplImage* lbp_face = cvCreateImage(cvGetSize(Gray_face), IPL_DEPTH_8U, 1); //先分配图像空间
			Mat face = imread(path,
					CV_LOAD_IMAGE_ANYDEPTH | CV_LOAD_IMAGE_ANYCOLOR);
			//在这里直接转换成LBP
			Mat lbp_face = Mat::zeros(face.size(), face.type());
			olbp_<uchar>(face, lbp_face);
			images.push_back(lbp_face);
			stringstream st;
			st << path << "lbp_face.jpg";
			cout << st.str() << endl;
			imwrite(st.str(), lbp_face);
			labels.push_back(atoi(classlabel.c_str()));
		}
	}
}

bool train(string fn_csv, string output_file);

int recognize_user(string model_data_path, string imag_path);
//
//int main(int argc, const char *argv[]) {
//	// Check for valid command line arguments, print usage
//	// if no arguments were given.
////	if (argc != 3) {
////		cout << "usage: " << argv[0] << " <csv file> <output name>" << endl;
////		exit(1);
////	}
////	// Get the path to your CSV.
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
//
//}

bool train(string fn_csv, string output_file) {
	// These vectors hold the images and corresponding labels.
	vector<Mat> images;
	vector<int> labels;
	// Read in the data. This can fail if no valid
	// input filename is given.
	try {
		read_csv(fn_csv, images, labels);
	} catch (cv::Exception& e) {
		cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg
				<< endl;
		// nothing more we can do
		return false;
	}
	// Quit if there are not enough images for this demo.
	if (images.size() <= 1) {
		string error_message =
				"This demo needs at least 2 images to work. Please add more images to your data set!";
		CV_Error(Error::StsError, error_message);
	}
	// The following lines simply get the last images from
	// your dataset and remove it from the vector. This is
	// done, so that the training data (which we learn the
	// cv::LBPHFaceRecognizer on) and the test data we test
	// the model with, do not overlap.
//	Mat testSample = images[images.size() - 1];
//	int testLabel = labels[labels.size() - 1];
//	images.pop_back();
//	labels.pop_back();
	// The following lines create an LBPH model for
	// face recognition and train it with the images and
	// labels read from the given CSV file.
	//
	// The LBPHFaceRecognizer uses Extended Local Binary Patterns
	// (it's probably configurable with other operators at a later
	// point), and has the following default values
	//
	//      radius = 1
	//      neighbors = 8
	//      grid_x = 8
	//      grid_y = 8
	//
	// So if you want a LBPH FaceRecognizer using a radius of
	// 2 and 16 neighbors, call the factory method with:
	//
	//      cv::createLBPHFaceRecognizer(2, 16);
	//
	// And if you want a threshold (e.g. 123.0) call it with its default values:
	//
	//      cv::createLBPHFaceRecognizer(1,8,8,8,123.0)
	//
	Ptr<LBPHFaceRecognizer> model = createLBPHFaceRecognizer();
	model->setThreshold(0);
	model->train(images, labels);
//	model->setLabelInfo(labels[0], "肇始于");

	model->save(output_file);
	// The following line predicts the label of a given
	// test image:
	int predicted = -1;
	double confidence = 0.0;
//	model->predict(testSample, predicted, confidence);
	string result_message = format("Predicted = %d / confidence = %f.",
			predicted, confidence);
	cout << result_message << endl; // First we'll use it to set the threshold of the LBPHFaceRecognizer // to 0.0 without retraining the model. This can be useful if // you are evaluating the model: // model->setThreshold(0.0);
	// Now the threshold of this model is set to 0.0. A prediction
	// now returns -1, as it's impossible to have a distance below
	// it
//	predicted = model->predict(testSample);
//	cout << "Predicted class = " << predicted << endl;
	// Show some informations about the model, as there's no cool
	// Model data to display as in Eigenfaces/Fisherfaces.
	// Due to efficiency reasons the LBP images are not stored
	// within the model:
	cout << "Model Information:" << endl;
	string model_info =
			format(
					"\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
					model->getRadius(), model->getNeighbors(),
					model->getGridX(), model->getGridY(),
					model->getThreshold());
	cout << model_info << endl;
	vector<Mat> histograms = model->getHistograms();
	cout << "Size of the histograms: " << histograms[0].total() << endl;
	return true;
}

int recognize_user(string model_data_path, string imag_path) {
	Ptr<LBPHFaceRecognizer> model = createLBPHFaceRecognizer();
	model->load(model_data_path);

	cv::Mat img = imread(imag_path, CV_LOAD_IMAGE_GRAYSCALE);

	cout << "img: " << imag_path << endl;

	return recognize_user(model, img);
}

int recognize_user(Ptr<LBPHFaceRecognizer> model, cv::Mat img) {
//	Ptr<LBPHFaceRecognizer> model = createLBPHFaceRecognizer();
//	model->load(model_data_path);

//	cv::Mat img = imread(imag_path, CV_LOAD_IMAGE_GRAYSCALE);

//	cout << "img: " << imag_path << endl;
	int predictedLabel = -1;

	double predicted_confidence = 0.0;
	// Get the prediction and associated confidence from the model
	model->predict(img, predictedLabel, predicted_confidence);

	cout << "predictedLabel:" << predictedLabel << endl;
//	cout << model->getLabelInfo(predictedLabel) << endl;
	return predictedLabel;
}

