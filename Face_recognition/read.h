#ifndef READ_H
#define READ_H
#include <opencv2/opencv.hpp>
using namespace std;

class image_content {
public:
	int height;
	int width;
	int content[112*92];         //contents[all pixels]
};

class image_content_matrix {
public:
	int matrix[400][112*92];     //store all image information in 2 dimesion, [number of all images][all pixels]
};

namespace read {
	int video(string path);
    image_content figure(string path);
}

#endif