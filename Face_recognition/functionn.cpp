#include <opencv2/opencv.hpp>
#include "information.h"
#include "functionn.h"
using namespace cv;
using namespace std;

vector<int> functionn::summ(vector<vector<int>> image_matrix) {


	vector<int> total(figure_height*figure_width,0);
	
	for (int i = 0; i < number_of_dataset; i++) {
		for (int j=0;j < figure_height*figure_width;j++) {
			total[j]= total[j] + image_matrix[i][j];
		}
	}
	
    return total;


};

vector<int> functionn::averagee(vector<vector<int>> image_matrix) {


	vector<int> average(figure_height*figure_width, 0);

	for (int i = 0; i < number_of_dataset; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			average[j] = average[j] + image_matrix[i][j];
		}
	}


	for (int j = 0; j < figure_height*figure_width; j++) {
		average[j] = average[j]/ number_of_dataset;
	}
	return average;


};
