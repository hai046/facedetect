#include "opencv2/core.hpp"
#include "opencv2/face.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace cv;
using namespace cv::face;
using namespace std;

bool train(string fn_csv, string output_file);

int recognize_user(string model_data_path, string imag_path);

int recognize_user(Ptr<LBPHFaceRecognizer> model, cv::Mat img);
