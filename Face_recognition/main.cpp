#include<iostream>
#include <cstdio>
#include <string>
#include "read.h"

using namespace std;

//#define input "video.mp4"
//#define input "image.jpg"
//#define input "att_faces/s1/1.pgm"

string input,indicator1,indicator2 ;
string dataset = "ATT/";
string dash = "_";
string file_type = ".png";
int number_of_dataset = 400;


int main() {


	image_content image;
	image_content_matrix all_image;
	cout << "Input is : " << input << endl;




    for (int i = 0, q=1 , w=1; i < number_of_dataset && q < 41 && w < 11; i++) {
	    indicator1 = to_string (q);
	    indicator2 = to_string (w);
	    input = dataset + indicator1 + dash + indicator2 + file_type;   
		cout << input << endl;                                          
		image = read::figure(input);                                    //read figure and return data in "class imagecontent" which have the pixels data in matrix form
	    for (int j = 0; j < image.height*image.width; j++) {
			all_image.matrix[i][j] = int(image.content[j]);             //store all figures to one martix
	    }
		if (w < 11) {
			w++;
		}
		if (w == 11) {
			w = 1;
			q++;
		}
    }

	system("pause");
}