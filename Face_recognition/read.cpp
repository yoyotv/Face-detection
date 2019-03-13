#include <opencv2/opencv.hpp>
#include "information.h"
#include "read.h"
using namespace cv;
using namespace std;


image_content read::figure(string path)
{
	Mat image;
	image_content image_output;
	image = imread(path, 0);   // Read the file


	
	//namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	//imshow("Display window", image);                   // Show our image inside it.
	



	waitKey(0);                // Wait for a keystroke in the window

	image_output.width = image.cols;
	image_output.height = image.rows;

	
	for (int i = 0,count = 0; i < image_output.height; i++) {
		for (int j = 0; j < image_output.width; j++) {
			image_output.content[count] = image.at<uchar>(i, j);  //store the pixel value from Mat to int
			count++;
		}
	}

	return image_output;
}



int read::video(string input) {

	VideoCapture video(input);
	if (!video.isOpened()) {
		return -1;
	}
	Size videoSize = Size((int)video.get(CV_CAP_PROP_FRAME_WIDTH), (int)video.get(CV_CAP_PROP_FRAME_HEIGHT));
	namedWindow("video demo", CV_WINDOW_AUTOSIZE);
	Mat videoFrame;

	while (true) {
		video >> videoFrame;
		if (videoFrame.empty()) {
			break;
		}
		imshow("video demo", videoFrame);
		waitKey(33);
	}
	return 0;
}





