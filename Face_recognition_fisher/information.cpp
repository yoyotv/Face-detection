#include "information.h"
#include <math.h>
extern double all_image_matrix[number_of_dataset][figure_height*figure_width];
extern vector<double> average_face;
extern vector<double> each_eigenvector;
extern vector<vector<double>> eigenvectors;
using namespace std;
extern int test_index;
extern double class_average_face[number_of_face_class][figure_height*figure_width];
extern double class_w[number_of_face_class][number_of_eigenvectors];

void Execute::calculate_w(double face[]) {
	for (int i = 0; i < number_of_eigenvectors; i++) {
		w[i] = 0;
		for (int j = 0; j < figure_height*figure_width; j++) {
			w[i] = w[i] + eigenvectors[i][j]*(face[i] - average_face[i]);
			//cout << eigenvectors[i][j] << endl;
			//cout << face[i] << endl;
			//cout << w[i] << endl;
		}
	}
}


void class_information::calculate_all_average_face() {
	//Let's calculate the average face of all class
	vector<double> class_A(figure_height*figure_width, 0);	
	for (int i = 0; i < number_of_face_class; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			int k = i*10;
			for (int g = 0; g < 10 ;g++) {
				class_average_face[i][j] = class_average_face[i][j] + all_image_matrix[k][j];
				k++;
			}                                                                          //0~9
		}


	}
	for (int i = 0; i < number_of_face_class; i++) {
		for (int j = 0; j < figure_height*figure_width; j++) {
			class_average_face[i][j] = class_average_face[i][j] / 10;
		}
	}
	//Apply the average face of class A to eigenfaces 




};







void class_information::calculate_all_w() {
	for (int k = 0; k < number_of_face_class; k++) {
		calculate_w(class_average_face[k]);
		for (int j = 0; j < number_of_eigenvectors; j++) {
			class_w[k][j] = w[j];
		}
	}

};




void classify::criteria_each() {   //if choice =1 or~~


	int current = 0;
	int next = 1;
	for (int j = 0; j < number_of_face_class - 1; j++) {
		double e_distance_compare_with_current = 0;
		double e_distance_compare_with_next = 0;
		for (int i = 0; i < 6; i++) {
			e_distance_compare_with_current = sqrt(e_distance_compare_with_current + pow(w[i] - class_w[current][i], 2));
			e_distance_compare_with_next = sqrt(e_distance_compare_with_next + pow(w[i] - class_w[next][i], 2));
		}
		if ((e_distance_compare_with_current) < (e_distance_compare_with_next)) {
			criteria_answer = current;
			next++;
		}
		else {
			criteria_answer = next;
			current = next;
			next++;
		}
	}

}


void classify::criteria() {   //if choice =1 or~~
	int current_result;
	double input2[figure_height*figure_width];
	for (int k = 0; k < choice; k++) {
		for (int h = 0; h < figure_height*figure_width; h++) {
			input2[h] = all_image_matrix[k][h];
		}
		//Apply face with eigenvector1~6
		calculate_w(input2);
		criteria_each();
		current_result = criteria_answer;
		all_result[k] = current_result; 
		cout << current_result << endl;
	}
}




int classify::determine_result() {
	if (choice == 1) {
		//cout << "According to the Euclidian distance and Equation(8)" << endl;
		//cout << "The determine is Class " << criteria_answer << " !" << endl;
		return criteria_answer;
	}


}



