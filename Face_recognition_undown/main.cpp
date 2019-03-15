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
double class_average_face[number_of_face_class][figure_height*figure_width] = { 0 };
double class_w[number_of_face_class][number_of_eigenvectors] = { 0 };
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


		//This part is saving the image to a txt, in order to double check the matrix of input figure is correctly save into class "image_content" or not.
		//We save all data into a txt, then display it to check whether it is the original image or not.
		/*
		ofstream file;
		for (int i=0; i < image.height*image.width; i++) {

		file.open("test1.txt",fstream::app);
		file << image.content[i];
		file << "\n";
		file.close();
		cout << i << endl;
		cout << "\n";
		}
		cout << endl;
		*/

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
	vector<vector<double>> A_matrix = functionn::calculate_A(all_image_matrix, average_face);
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


	//********
	//This is the eigen way
	//vector<vector<complex<double>>> eigenvectors = functionn::calculate_eigenvalues_and_eigenvectors(A_matrix);
	//********




	//Now we have the eigenvector(eigenface)!
	//Let's display our eigenface !


	//////////////////////////////////////////////////////////////////////////////////
	/*
	//This part is reflecting the pixel value to (0,1), then reflect it to (0,255)
	
	cout << eigenvectors[0][100] << endl;
	double maximum = 0;
	double minimum = 1;
	for (int count = 0; count < figure_height*figure_width; count++) {
		maximum = max(maximum, eigenvectors[display_index][count]);
		minimum = min(minimum, eigenvectors[display_index][count]);
	}

	for (int count = 0; count < figure_height*figure_width; count++) {
		eigenvectors[display_index][count] = (eigenvectors[display_index][count] - minimum) / (maximum - minimum) * 255;
	}

	//Finish reflecting to (0,255)!
	//////////////////////////////////////////////////////////////////////////////////


	//Assign the value in eigenface to file m (opencv Mat form) in order to display.
	if (eigenvectors[display_index].size() == figure_height*figure_width) // check that the rows and cols match the size of your vector
	{
		cv::Mat m(figure_height, figure_width, CV_8U); // initialize matrix of uchar of 1-channel where you will store vec data

		int p3 = 0;
		for (int p1 = 0; p1 < figure_height; p1++) {
			for (int p2 = 0; p2 < figure_width; p2++) {
				m.at<uchar>(p1, p2) = eigenvectors[display_index].at(p3);
				p3++;
			}
		}

		cv::imwrite("Eigenface.jpg", m);               //Save the eigenface!
	}

	*/
	//Now we have the essiential item to recognize face!














	//Choose a image.
	//Apply it with eigenfaces.










	//all_data.set_all_imagematrix(image_matrix);
	//all_data.set_average_face(average_face);



	//Execute one_image;
	//one_image.calculate_w(all_data.all_image_matrix[test_index]);



	class_information all;





	//First calculate the aveverge face of each class

	all.calculate_all_average_face();



	//Let's calculate each omega of all classes
	all.calculate_all_w();


	//Now we got 40 omega(each omega indicates the weights of each class and has 6 dimensions(number_of_eigenvectors))
	//Definition of Omega refers to equation(8) in "Eigenfaces for Recognition" 1991.

	//Let's classify our image from class A, B and C!
	//Use equation(8) in "Eigenfaces for Recognition" 1991.



	//Assign testing data
	double test_data[number_of_test_data][figure_height*figure_width];

	for (int i = 0; i < choice; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			test_data[i][j] = all_image_matrix[i][j];
		}
	}

	
	classify result;
	result.criteria();                          //Calculate the Euclidian distance
	result.determine_result();








	cout << endl;
	system("pause");
}


