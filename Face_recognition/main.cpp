#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <fstream>
#include "information.h"
#include "function.h"
#include "read.h"

using namespace std;


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

	//Create a file to save matrix of figure
	//ofstream file;



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
	
         








	//vector<int> average_face = function::summ(image_matrix);
	vector<int> average_face = function::averagee(image_matrix);




	cout << average_face.at(0);





	system("pause");
}