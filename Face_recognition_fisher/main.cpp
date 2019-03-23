#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <Eigen/Eigenvalues>
#include <opencv2/opencv.hpp>
#include <algorithm> 
#include <math.h>


#include "information.h"
#include "functionn.h"
#include "read.h"

using namespace std;
using Eigen::MatrixXd;
using Eigen::EigenSolver;
using Eigen::VectorXcd;
using Eigen::MatrixXcd;


string input,indicator1,indicator2 ;
string dataset = "ATT/";
string dash = "_";
string file_type = ".png";

double all_image_matrix[number_of_dataset][figure_height*figure_width] = { 0 };             //Create a vector*vector to store all image
vector<double> average_face;
vector<double> each_eigenvector(figure_height*figure_width,0);
vector<vector<double>> eigenvectors(number_of_eigenvectors,each_eigenvector);
vector<vector<double>> Wfldupeigenvectors(number_of_eigenvectors, each_eigenvector);
vector<vector<double>> Wflddowneigenvectors(number_of_eigenvectors, each_eigenvector);
double class_average_face[number_of_face_class][figure_height*figure_width] = { 0 };
double class_w[number_of_face_class][number_of_eigenvectors] = { 0 };
int test_index;
int main() {

	image_content image;                                                   //Create a class call "image_content" to store the information of image
	double each[figure_height*figure_width] = {0};                       //Create a vector to store one image



	//Data all_data;
	

	//Read and store the data from figure and store it into to image_matrix
	for (int i = 0, q = 1, w = 1; i < number_of_dataset && q < 41 && w < 11; i++) {
		indicator1 = to_string(q);
		indicator2 = to_string(w);
		input = dataset + indicator1 + dash + indicator2 + file_type;      //Read the file by substituting the character.
		image = read::figure(input);                                       //Via opencv to read the image and acquire the data in class "image_content" form.
		for (int j = 0; j < figure_height*figure_width; j++) {
			each[j] = (image.content[j]);                                  // Assign the data from class "image_content" to vector variable "each".
		}

		//Store information of each figure to the image_matrix
		for (int k = 0; k < figure_height*figure_width; k++) {
			all_image_matrix[i][k] = each[k];
		}

		//This is just for the pointer.
		if (w < 11) { w++; }
		if (w == 11) { w = 1; q++; }
	}

	average_face = functionn::averagee(all_image_matrix);    //Feed the image_matrix to the function and acquire the average face.

	functionn::save_one_face(average_face);                     //This part is saving the average face to a txt, in order to double check the average face is normal or not.


	//********
	functionn::calculate_St();
	functionn::calculate_Sb();
	functionn::calculate_Sw();
	//return Wopt


	//We got A!  (A = A_matrix)
	//********

	///////////////////////////////////////////////////////////////////////////////
	// Let's calculate eigenvectors!

	//We have two ways to calculate eigenvectors, first is via Matlab, the other is eigen.

	//This part is reading the eigenvector and eigenvalue which are calculated from matlab.
	//Read 6 eigenvalues and its relevant eigenvetors.
	string file_name = "For_matlab/eigenvector";
	string file_type = ".txt";
	ifstream eigenvector_file;
	for (int i = 1; i <= number_of_eigenvectors; i++) {
		int j = 0;
		cout << file_name + to_string(i) + file_type << endl;
		eigenvector_file.open(file_name + to_string(i) + file_type, ios::in);
		string line;
		double tem;
		while (getline(eigenvector_file, line)) {
			tem = stod(line);
			eigenvectors[i - 1][j] = tem;
			j++;
		}
		eigenvector_file.close();
	}

	
	//Now we have the essiential item to recognize face!
	int per = 0;
	int test_index = 0;
	while (true) {
		//cout << "Please tell me which image do you want to test? (0~49) or enter -1 to exit" << endl;
		//cin >> test_index;
		//cout << endl;

		class_information all;
		//First calculate the aveverge face of each class
		all.calculate_all_average_face();

		//Let's calculate each omega of all classes
		all.calculate_all_w();


		classify result;

		result.calculate_w(all_image_matrix[test_index]);
		result.criteria_each();                          //Calculate the Euclidian distance
		int d_ans=result.determine_result();



		int ans;
		if (test_index < 10) {
			ans = 0;
		}
		else if (test_index < 20) {
			ans = 1;
		}
		else if (test_index < 30) {
			ans = 2;
		}
		else if (test_index < 40) {
			ans = 3;
		}
		else if (test_index < 50) {
			ans = 4;
		}
		else if (test_index < 60) {
			ans = 5;
		}
		else if (test_index < 70) {
			ans = 6;
		}
		else if (test_index < 80) {
			ans = 7;
		}
		else if (test_index < 90) {
			ans = 8;
		}
		else if (test_index < 100) {
			ans = 9;
		}

		//cout << "And the ground truth is " << ans << " !" << endl;



		//cout << endl;


		if (ans == d_ans) {
			per = per + 1;
		}

		if (test_index == number_of_dataset) {
			double acc = double(per) / double(number_of_dataset);
			cout << "Accuracy=" << acc*100 << " %" << " !" << endl;
			break;
		}
		test_index = test_index + 1;
	}
	system("pause");
}


