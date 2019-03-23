#ifndef INFORMATION_H
#define INFORMATION_H
#include <Eigen/Eigenvalues>
#include <vector>
#include <iostream>
#include <math.h>
using namespace std;

#define number_of_dataset 50
#define figure_height 112
#define figure_width 92
#define number_of_eigenvectors 6
#define display_index 0
#define number_of_face_class 5
#define number_of_image_of_each_class 10
#define number_of_test_data 1
extern int test_index;

const int test_data_ground_truth[30] = { 0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2};

const int choice = number_of_test_data;

extern double image_matrix[number_of_dataset][figure_height*figure_width];
extern vector<double> average_face;



class Execute{
public:	
	double w[number_of_eigenvectors];
	void calculate_w(double face[]);
};


class class_information :public Execute {
public:

	void calculate_all_average_face();
	void calculate_all_w();
};



class classify:public class_information {
public:
	string which;
	double percentage=0;
	int criteria_answer=0;
	int all_result[number_of_test_data];
	void criteria_each();            //Calculate the Euclidian distance
	void criteria();         //Calculate the Euclidian distance

	int determine_result();   


};




#endif