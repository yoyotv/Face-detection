#ifndef READ_H
#define READ_H
#include <opencv2/opencv.hpp>

#define figure_height 112
#define figure_width 92

using namespace std;


class image_content {
public:
	int height;
	int width;
	int content[figure_height *figure_width];         //contents[all pixels]
};


namespace read {
	int video(string path);
    image_content figure(string path);
}

#endif