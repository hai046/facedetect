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

int makeFacedetect(string cascadeName, string path, string saveFilePath);
string detectAndDraw(bool showImage, string name, Mat& img,
		CascadeClassifier& cascade, CascadeClassifier& nestedCascade,
		double scale, bool tryflip);
vector<string> scanFile(string path);

int readFacedetect(string cascadeName, string inputName);

