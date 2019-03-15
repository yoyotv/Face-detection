#include <opencv2/opencv.hpp>
#include <fstream>
#include "information.h"
#include "functionn.h"

using namespace cv;
using namespace std;
extern int test_index;
vector<double> functionn::summ(vector<vector<double>> image_matrix) {


	vector<double> total(figure_height*figure_width,0);
	
	for (int i = 0; i < number_of_dataset; i++) {
		for (int j=0;j < figure_height*figure_width;j++) {
			total[j]= total[j] + image_matrix[i][j];
		}
	}
	
    return total;


};

vector<double> functionn::averagee(double image_matrix[number_of_dataset][figure_height*figure_width]) {


	vector<double> average(figure_height*figure_width, 0);

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



double functionn::save_one_face(vector<double> face) {

	////////////////////////////////////////////////////////////////////////////////////////
	//This part is saving the average face to a txt, in order to double check the average face is normal or not.
	//Create a file to save matrix of figure

	ofstream file;

	for (int i=0; i < figure_height*figure_width; i++) {

	file.open("average_face.txt",fstream::app);
	file << face.at(i);
	file << "\n";
	file.close();
	}

	return 0;
	//This part is saving the image to a txt, in order to double check the matrix of figure is correct or not.
	////////////////////////////////////////////////////////////////////////////////////////////


}





vector<vector<double>> functionn::calculate_A(double image_matrix[number_of_dataset][figure_height*figure_width], vector<double> average_face) {

	///////////////////////////////////////////////////////////////////////////////////////////////////
	//This part is to calculate A  in form vector.

	vector<double> a(figure_height*figure_width, 0);
	vector<vector<double>> A_matrix(figure_height*figure_width, a);


	ofstream file;                           		//This part is storing every face to double check the data is correct or not.
	file.open("For_matlab/test2.txt", fstream::app);		    //This part is storing every face to double check the data is correct or not.

	//Calculate the A_matrix
	for (int i = 0; i < number_of_dataset; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			a[j] = image_matrix[i][j] - average_face[j];  //a
			if (a[j] < 0) { a[j] = 0; };
		}
	    ///////////////////////////////////////////////////////////////
		//This part is storing every face to double check the data is correct or not.
		//Write the data into a txt.  txt(400*112*92)
		
		for (int k = 0; k < figure_height*figure_width; k++) {
			file << a.at(k);
			file << "\n";
		}
		
		//Now we have the data of every image in (400*112*92)
		//Feed this "test2.txt" to "For_matlab/matlab_eigen", and then we can acquire eigenvectors calculates from matlab.
		///////////////////////////////////////////////////////////////
		//This part is to generate A matrix
		/*
		for (int k = 0; k < figure_height*figure_width;k++) {
			for (int m = 0; m < figure_height*figure_width; m++) {
				A_matrix[k][m] = A_matrix[k][m] + a[k] * a[m];
			}
		}
		*/
		cout << i << endl;
	}
	file.close();


	/*
	//divide by number_of_dataset
	for (int k = 0; k < figure_height*figure_width; k++) {
		for (int m = 0; m < figure_height*figure_width; m++) {
			A_matrix[k][m] = A_matrix[k][m] / number_of_dataset;
		}
	}
	*/

	return A_matrix;
	//We got A!  (A = A_matrix)
	//////////////////////////////////////////////////////////////////////////////////////////////////


}




vector<vector<complex<double>>> functionn::calculate_eigenvalues_and_eigenvectors(vector<vector<double>> A_matrix) {
	//Let's calculate eigenvector and eigenvalue!
	MatrixXd A(figure_height*figure_width, figure_height*figure_width);   //Delcare a MatrixXd in order to use the eigen function to calculate eigenvector.
    
	//Assign the data from A_matrix(vector form) to A(MatrixXd form).

	for (int i = 0; i < figure_height*figure_width; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			A(i, j) = double(A_matrix[i][j]);
		}
	}

	
	cout << "Here is the matrix, A" << endl << endl << endl;
	EigenSolver<MatrixXd> es(A);
	cout << "The eigenvalues of A are:" << endl << es.eigenvalues() << endl;
	complex<double> lambda = es.eigenvalues()[0];
	cout << "Consider the biggest eigenvalue, lambda = " << lambda << endl;
	//VectorXcd v = es.eigenvectors();
	VectorXcd v = es.eigenvectors();
	cout << "If v is the corresponding eigenvector, then it is " << endl << v.col(0) << endl;
	

	//Convert it to form "vector"
	vector<double> each_eigenvector(figure_height*figure_width, 0);                       //Create a vector to store one image
	//vector<vector<complex<double>>> eigenvectors(number_of_eigenvectors, each_eigenvector);             //Create a vector*vector to store all image
	vector<vector<complex<double>>> eigenvectors;
	
	for (int i = 0; i < number_of_eigenvectors; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			eigenvectors[i][j] = (v(i,j));
		}
	}
	


	return eigenvectors;
	//Now we have the eigenvector(eigenface)!
	//Let's display our eigenface !



///////////////////////////////////////////////////////////////////////////////
}

