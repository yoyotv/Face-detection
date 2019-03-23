#ifndef FUNCTIONN_H
#define FUNCTIONN_H
#include <Eigen/Eigenvalues>
using Eigen::MatrixXd;
using Eigen::EigenSolver;
using Eigen::VectorXcd;
using Eigen::MatrixXcd;
using namespace std;

extern int test_index;
namespace functionn {
	vector<double> summ(vector<vector<double>> image_matrix);
	vector<double> averagee(double image_matrix[number_of_dataset][figure_height*figure_width]);
	double save_one_face(vector<double> face);

	vector<vector<complex<double>>> calculate_eigenvalues_and_eigenvectors(vector<vector<double>> A_matrix);
	void calculate_St();
	void calculate_Sb();
	void calculate_Sw();
	


}




#endif