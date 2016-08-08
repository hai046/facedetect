#include "opencv2/objdetect.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"

#include "opencv2/videoio/videoio_c.h"
#include "opencv2/highgui/highgui_c.h"

#include <cctype>
#include <iostream>
#include <iterator>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
#include <errno.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>

using namespace std;
using namespace cv;

/**
 * 检索图片目录 path    然后根据现有的模型 cascadeName 识别出人脸，并建立正样本的描述文件  格式是 fileName num  x y w h x2 y2 w2 h2 ……【具体定义可以查官方文档】
 */
int makeFacedetect(string cascadeName, string path, string saveFilePath);

/**
 * 检查人脸，如果showImage 则可以显示出来
 */
string detectAndDraw(bool showImage, string name, Mat& img,
		CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
		double scale, bool tryflip, string model_path = "");
vector<string> scanFile(string path);

/**
 * 显示识别
 */
int readFacedetect(string cascadeName, string inputName, string model_path);

