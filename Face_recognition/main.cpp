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


int main() {


	

	image_content image;                                                   //Create a class call "image_content" to store the information of image
	vector<int> each(figure_height*figure_width, 0);                       //Create a vector to store one image
	vector<vector<int>> image_matrix(number_of_dataset, each);             //Create a vector*vector to store all image


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
			image_matrix[i][k] = each[k];
		}

		//This is just for the pointer.
		if (w < 11) { w++; }
		if (w == 11) { w = 1; q++; }
	}



    
	vector<int> average_face = functionn::averagee(image_matrix);    //Feed the image_matrix to the function and acquire the average face.




	////////////////////////////////////////////////////////////////////////////////////////
	//This part is saving the average face to a txt, in order to double check the average face is normal or not.
	//Create a file to save matrix of figure
	/*
	ofstream file;

	for (int i=0; i < image.height*image.width; i++) {

	file.open("test.txt",fstream::app);
	file << average_face.at(i);
	file << "\n";
	file.close();
	}
	*/
	//This part is saving the image to a txt, in order to double check the matrix of figure is correct or not.
    ////////////////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////////////////
	// A * eigenvector = eigenvalue * eigenvector
	// We have two forms to calculate A, this part is via eigen library MatrixXd
	/*
	MatrixXd a(1, figure_height*figure_width);
	MatrixXd a2( figure_height*figure_width,1);
	MatrixXd A_matrix;
	//MatrixXd A_matrix(figure_height*figure_width, figure_height*figure_width);
	//A_matrix.setZero();
	MatrixXd number_of_dataset_matrix(1, figure_height*figure_width);

	for (int k = 0; k < figure_height*figure_width; k++) {
		number_of_dataset_matrix(0, k) = number_of_dataset;
	}


	//Calculate the A_matrix
	for (int i = 0; i < number_of_dataset; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			a(j) = image_matrix[i][j] - average_face[j];   //a
			if (a(j) < 0) { a(j) = 0; };
		}
		a2 = a.transpose();
		A_matrix = a2 * a;
		cout << A_matrix(0, 0);
		//A_matrix = A_matrix + a.inverse() * a;

	}





	A_matrix.array() = A_matrix.array() * (1/number_of_dataset_matrix.array());
	*/
	//We got A!  (A = A_matrix)
	//////////////////////////////////////////////////////////////////////////////////////////////////



	
    ///////////////////////////////////////////////////////////////////////////////////////////////////
	//This part is to calculate A  in form vector.
	/*
	vector<int> a(figure_height*figure_width, 0);
	vector<vector<int>> A_matrix(figure_height*figure_width, a);
	vector<vector<int>> *A_tem_matrix;

	ofstream file;                           		//This part is storing every face to double check the data is correct or not.
	file.open("test2.txt", fstream::app);		    //This part is storing every face to double check the data is correct or not.

	//Calculate the A_matrix
	for (int i = 0; i < number_of_dataset; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			a[j] = image_matrix[i][j] - average_face[j];  //a
			if (a[j] < 0) { a[j] = 0; };
		}
		///////////////////////////////////////////////////////////////
		//This part is storing every face to double check the data is correct or not.
		//Write the data into a txt.  txt(400*112*92)
		for (int k = 0; k < image.height*image.width; k++) {
			file << a.at(k);
			file << "\n";
		}
		//Now we have the data of every image in (400*112*92)
		//Feed this "test2.txt" to "For_matlab/matlab_eigen", and then we can acquire eigenvectors calculates from matlab.
		///////////////////////////////////////////////////////////////
		//This part is to generate A matrix
		
		for (int k = 0; k < figure_height*figure_width;k++) {
			for (int m = 0; m < figure_height*figure_width; m++) {
				A_matrix[k][m] = A_matrix[k][m] + a[k] * a[m];
			}
		}
		
		cout << i << endl;
	}
	//file.close();


	
	//divide by number_of_dataset
	for (int k = 0; k < figure_height*figure_width; k++) {
		for (int m = 0; m < figure_height*figure_width; m++) {
			A_matrix[k][m] = A_matrix[k][m] / number_of_dataset;
		}
	}



	




	*/
	//We got A!  (A = A_matrix)
	//////////////////////////////////////////////////////////////////////////////////////////////////


	//Let's calculate eigenvector and eigenvalue!

    /*
    MatrixXd A(figure_height*figure_width, figure_height*figure_width);   //Delcare a MatrixXd in order to use the eigen function to calculate eigenvector.

	//Assign the data from A_matrix(vector form) to A(MatrixXd form).
	for (int i = 0; i < figure_height*figure_width; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			A(i, j) = A_matrix[i][j];
		}
	}





	cout << "Here is the matrix, A" << endl << endl << endl;
	EigenSolver<MatrixXd> es(A);
	cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
	complex<double> lambda = es.eigenvalues()[0];
	cout << "Consider the biggest eigenvalue, lambda = " << lambda << endl;
	VectorXcd v = es.eigenvectors().col(0);
	cout << "If v is the corresponding eigenvector, then it is " << endl << v << endl;
	*/
	//Now we have the eigenvector(eigenface)!
	//Let's display our eigenface !





    ///////////////////////////////////////////////////////////////////////////////
    //This part is reading the eigenvector and eigenvalue which are calculated from matlab.
	//Read 6 eigenvalues and its relevant eigenvetors.

    double eigenvalue1 = 3435871.34359714;
	double eigenvalue2 = 645879.377709462;
	double eigenvalue3 = 362859.341695603;
	double eigenvalue4 = 345531.848411983;
	double eigenvalue5 = 310556.113653165;
	double eigenvalue6 = 195126.774881149;
	vector<double> eigenvector1(figure_height*figure_width, 0);
	vector<double> eigenvector2(figure_height*figure_width, 0);
	vector<double> eigenvector3(figure_height*figure_width, 0);
	vector<double> eigenvector4(figure_height*figure_width, 0);
	vector<double> eigenvector5(figure_height*figure_width, 0);
	vector<double> eigenvector6(figure_height*figure_width, 0);

    ifstream eigenvector_file1;
	eigenvector_file1.open("all_eigen_item/eigenvector1.txt", ios::in);
	string line1;
	double tem1;
	int i1 = 0;
	while (getline(eigenvector_file1, line1)) {
		tem1 = stod(line1);
		eigenvector1.at(i1) = tem1;
		i1++;

	}
	/////////////////////////
	ifstream eigenvector_file2;
	eigenvector_file2.open("all_eigen_item/eigenvector2.txt", ios::in);
	string line2;
	double tem2;
	int i2 = 0;
	while (getline(eigenvector_file2, line2)) {
		tem2 = stod(line2);
		eigenvector2.at(i2) = tem2;
		i2++;

	}
	/////////////////////////
	ifstream eigenvector_file3;
	eigenvector_file3.open("all_eigen_item/eigenvector3.txt", ios::in);
	string line3;
	double tem3;
	int i3 = 0;
	while (getline(eigenvector_file3, line3)) {
		tem3 = stod(line3);
		eigenvector3.at(i3) = tem3;
		i3++;

	}
	/////////////////////////
	ifstream eigenvector_file4;
	eigenvector_file4.open("all_eigen_item/eigenvector4.txt", ios::in);
	string line4;
	double tem4;
	int i4 = 0;
	while (getline(eigenvector_file4, line4)) {
		tem4 = stod(line4);
		eigenvector4.at(i4) = tem4;
		i4++;

	}
	/////////////////////////
	ifstream eigenvector_file5;
	eigenvector_file5.open("all_eigen_item/eigenvector5.txt", ios::in);
	string line5;
	double tem5;
	int i5 = 0;
	while (getline(eigenvector_file5, line5)) {
		tem5 = stod(line5);
		eigenvector5.at(i5) = tem5;
		i5++;

	}
	/////////////////////////
	ifstream eigenvector_file6;
	eigenvector_file6.open("all_eigen_item/eigenvector6.txt", ios::in);
	string line6;
	double tem6;
	int i6 = 0;
	while (getline(eigenvector_file6, line6)) {
		tem6 = stod(line6);
		eigenvector6.at(i6) = tem6;
		i6++;

	}
	
	//Finish read!
	///////////////////////////////////////////////////////////////////////////////



	//Now we have the eigenvector(eigenface)!
	//Let's display our eigenface !

	//////////////////////////////////////////////////////////////////////////////////
	//This part is reflecting the pixel value to (0,1), then reflect it to (0,255)
	double maximum = 0;
	double minimum = 1;
	for (int count = 0; count < figure_height*figure_width; count++) {
		maximum = max(maximum, eigenvector1[count]);
		minimum = min(minimum, eigenvector1[count]);
	}

	for (int count = 0; count < figure_height*figure_width; count++) {
		eigenvector1[count] = (eigenvector1[count] - minimum) / (maximum - minimum) * 255;
	}

	//Finish reflecting to (0,255)!
	//////////////////////////////////////////////////////////////////////////////////


	//Assign the value in eigenface to file m (opencv Mat form) in order to display.
	if (eigenvector1.size() == figure_height*figure_width) // check that the rows and cols match the size of your vector
	{
		cv::Mat m(figure_height, figure_width, CV_8U); // initialize matrix of uchar of 1-channel where you will store vec data
	
		int p3 = 0;
		for (int p1 = 0 ; p1 < figure_height; p1++) {
			for (int p2 = 0 ; p2 < figure_width; p2++) {
				m.at<uchar>(p1, p2) = eigenvector1.at(p3);
				p3++;
			}
		}

		cv::namedWindow("Eigenface1", figure_width *figure_height);
		cv::imshow("Eigenface1", m);
       
		cv::imwrite("Eigenface1.jpg", m);               //Save the eigenface!
	}

	
	//Now we have the essiential item to recognize face!

	


	//Choose a image.
	//Apply it with eigenfaces.
	int rand_num = 17;
	vector<double> w(6,0);
	for (int i = 0; i < figure_height*figure_width; i++) {
		w[0] = w[0] + eigenvector1.at(i)*(image_matrix[rand_num][i] - average_face[i]);
		w[1] = w[1] + eigenvector2.at(i)*(image_matrix[rand_num][i] - average_face[i]);
		w[2] = w[2] + eigenvector3.at(i)*(image_matrix[rand_num][i] - average_face[i]);
		w[3] = w[3] + eigenvector4.at(i)*(image_matrix[rand_num][i] - average_face[i]);
		w[4] = w[4] + eigenvector5.at(i)*(image_matrix[rand_num][i] - average_face[i]);
		w[5] = w[5] + eigenvector6.at(i)*(image_matrix[rand_num][i] - average_face[i]);
	}

	//Now we got the omega of the image that we want to claasify!
	//Definition of Omega refers to equation(8) in "Eigenfaces for Recognition" 1991.



	//Let's calculate the average face of class A 
	vector<double> class_A(figure_height*figure_width,0);
	for (int j=0; j < figure_height*figure_width; j++) {
		for (int i=0; i < 10; i++) {
			class_A[j] = class_A[j] + image_matrix[i][j];
		}
		class_A[j] = class_A[j] / 10;
	}

	//Apply the average face of class A to eigenfaces 

	vector<double> A_w(6, 0);
	for (int i=0; i < figure_height*figure_width; i++) {
		A_w[0] = A_w[0] + eigenvector1.at(i)*(class_A[i] - average_face[i]);
		A_w[1] = A_w[1] + eigenvector2.at(i)*(class_A[i] - average_face[i]);
		A_w[2] = A_w[2] + eigenvector3.at(i)*(class_A[i] - average_face[i]);
		A_w[3] = A_w[3] + eigenvector4.at(i)*(class_A[i] - average_face[i]);
		A_w[4] = A_w[4] + eigenvector5.at(i)*(class_A[i] - average_face[i]);
		A_w[5] = A_w[5] + eigenvector6.at(i)*(class_A[i] - average_face[i]);
	}

	//Now we got the omega of class A!

	//Let's calculate the average face of class B 
	vector<double> class_B(figure_height*figure_width, 0);
	for (int j = 0; j < figure_height*figure_width; j++) {
		for (int i = 10; i < 10+10; i++) {
			class_B[j] = class_B[j] + image_matrix[i][j];
		}
		class_B[j] = class_B[j] / 10;
	}

	//Apply the average face of class B to eigenfaces 

	vector<double> B_w(6, 0);
	for (int i= 0; i < figure_height*figure_width; i++) {
		B_w[0] = B_w[0] + eigenvector1.at(i)*(class_B[i] - average_face[i]);
		B_w[1] = B_w[1] + eigenvector2.at(i)*(class_B[i] - average_face[i]);
		B_w[2] = B_w[2] + eigenvector3.at(i)*(class_B[i] - average_face[i]);
		B_w[3] = B_w[3] + eigenvector4.at(i)*(class_B[i] - average_face[i]);
		B_w[4] = B_w[4] + eigenvector5.at(i)*(class_B[i] - average_face[i]);
		B_w[5] = B_w[5] + eigenvector6.at(i)*(class_B[i] - average_face[i]);
	}

	//Now we got the omega of class B!


	//Let's calculate the average face of class C 
	vector<double> class_C(figure_height*figure_width, 0);
	for (int j = 0; j < figure_height*figure_width; j++) {
		for (int i = 20; i < 10 + 10 + 10; i++) {
			class_C[j] = class_C[j] + image_matrix[i][j];
		}
		class_C[j] = class_C[j] / 10;
	}

	//Apply the average face of class C to eigenfaces 

	vector<double> C_w(6, 0);
	for (int i = 0; i < figure_height*figure_width; i++) {
		C_w[0] = C_w[0] + eigenvector1.at(i)*(class_C[i] - average_face[i]);
		C_w[1] = C_w[1] + eigenvector2.at(i)*(class_C[i] - average_face[i]);
		C_w[2] = C_w[2] + eigenvector3.at(i)*(class_C[i] - average_face[i]);
		C_w[3] = C_w[3] + eigenvector4.at(i)*(class_C[i] - average_face[i]);
		C_w[4] = C_w[4] + eigenvector5.at(i)*(class_C[i] - average_face[i]);
		C_w[5] = C_w[5] + eigenvector6.at(i)*(class_C[i] - average_face[i]);
	}

	//Now we got the omega of class C!


	//Let's classify our image from class A, B and C!
	//Use equation(8) in "Eigenfaces for Recognition" 1991.
	double e_distance_compare_with_A = 0;
	double e_distance_compare_with_B = 0;
	double e_distance_compare_with_C = 0;
	for (int i = 0; i < 6; i++) {
		e_distance_compare_with_A = e_distance_compare_with_A + pow(w[i] - A_w[i], 2);
		e_distance_compare_with_B = e_distance_compare_with_B + pow(w[i] - B_w[i], 2);
		e_distance_compare_with_C = e_distance_compare_with_C + pow(w[i] - C_w[i], 2);
	}

	e_distance_compare_with_A = sqrt(e_distance_compare_with_A);
	e_distance_compare_with_B = sqrt(e_distance_compare_with_B);
	e_distance_compare_with_C = sqrt(e_distance_compare_with_C);


	string Result;
	if (e_distance_compare_with_A < e_distance_compare_with_B && e_distance_compare_with_A < e_distance_compare_with_C) Result = "A";
	if (e_distance_compare_with_B < e_distance_compare_with_A && e_distance_compare_with_B < e_distance_compare_with_C) Result = "B";
	if (e_distance_compare_with_C < e_distance_compare_with_A && e_distance_compare_with_C < e_distance_compare_with_B) Result = "C";
	cout << "The Euclidian distance between Class A and test image is : " << e_distance_compare_with_A << endl;
	cout << "The Euclidian distance between Class B and test image is : " << e_distance_compare_with_B << endl;
	cout << "The Euclidian distance between Class C and test image is : " << e_distance_compare_with_C << endl;
	cout << "According to the Euclidian distance and Equation(8)" << endl;
	cout << "We can say test image is Class " << Result << " !" << endl;

	cout << endl;
	system("pause");
}