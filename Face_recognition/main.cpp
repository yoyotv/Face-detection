#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include <Eigen/Eigenvalues>

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


	image_content image;
	vector<int> each(figure_height*figure_width, 0);
	vector<vector<int>> image_matrix(number_of_dataset, each);

	//vector<int> image_matrix[number_of_dataset];     	//setup the empty image matrix to store the whole data (400 figures and 112*90 each)
	cout << "Input is : " << input << endl;





	//Read and store the data from figure and store it into to image_matrix
	for (int i = 0, q = 1, w = 1; i < number_of_dataset && q < 41 && w < 11; i++) {
		indicator1 = to_string(q);
		indicator2 = to_string(w);
		input = dataset + indicator1 + dash + indicator2 + file_type;
		image = read::figure(input);
		for (int j=0; j < figure_height*figure_width; j++) {
			each[j] = (image.content[j]);
		}


		//This part is saving the image to a txt, in order to double check the matrix of figure is correct or not. 
		/*
		for (int i=0; i < image.height*image.width; i++) {

		file.open("test.txt",fstream::app);
		file << image.content[i];
		file << "\n";
		file.close();
		cout << i << endl;
		cout << "\n";
		}
		cout << endl;
		*/

		//Store information of each figure to the image_matrix
		for (int k=0; k < figure_height*figure_width; k++) {
			image_matrix[i][k] = each[k];  
		}

		if (w < 11) {w++;}
		if (w == 11) {w = 1;q++;}
	}
	
         








	//vector<int> average_face = functionn::summ(image_matrix);
	vector<int> average_face = functionn::averagee(image_matrix);




	/*
	//This part is saving the image to a txt, in order to double check the matrix of figure is correct or not. 
	//Create a file to save matrix of figure
	ofstream file;

	for (int i=0; i < image.height*image.width; i++) {

	file.open("test.txt",fstream::app);
	file << average_face.at(i);
	file << "\n";
	file.close();
	}
	*/
	
	vector<int> a(figure_height*figure_width, 0);
	vector<vector<int>> A_matrix(number_of_dataset, a);
	vector<vector<int>> *A_tem_matrix;

	//Calculate the A_matrix
	for (int i = 0; i < number_of_dataset; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			a[j] = image_matrix[i][j] - average_face[j];                 //a
		}

		for (int k = 0; k < figure_height*figure_width; k++) {
			for (int m = 0; m < figure_height*figure_width; m++) {
				A_matrix[k][m] = A_matrix[k][m] + a[k] * a[m];
			}
			                 //a
		}
	}
	//divide by number_of_dataset
	for (int k = 0; k < figure_height*figure_width; k++) {
		for (int m = 0; m < figure_height*figure_width; m++) {
			A_matrix[k][m] = A_matrix[k][m] / number_of_dataset;
		}
	}

	
	//A_matrix*u=lamda*u







    MatrixXd A;
	for (int k = 0; k < figure_height*figure_width; k++) {
		for (int m = 0; m < figure_height*figure_width; m++) {
			A(k,m) = A_matrix[k][m] ;
		}
	}






	/*
	MatrixXd A = MatrixXd::Random(6, 6);
	cout << "Here is a random 6x6 matrix, A:" << endl << A << endl << endl;
	EigenSolver<MatrixXd> es(A);
	cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
	cout << "The matrix of eigenvectors, V, is:" << endl << es.eigenvectors() << endl << endl;
	complex<double> lambda = es.eigenvalues()[0];
	cout << "Consider the first eigenvalue, lambda = " << lambda << endl;
	VectorXcd v = es.eigenvectors().col(0);
	cout << "If v is the corresponding eigenvector, then lambda * v = " << endl << lambda * v << endl;
	cout << "... and A * v = " << endl << A.cast<complex<double> >() * v << endl << endl;
	MatrixXcd D = es.eigenvalues().asDiagonal();
	MatrixXcd V = es.eigenvectors();
	cout << "Finally, V * D * V^(-1) = " << endl << V * D * V.inverse() << endl;
	*/




























	cout << endl;
	



	system("pause");
}