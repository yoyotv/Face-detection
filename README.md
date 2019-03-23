# Face-detection-and-recognition
Face detection and recognition without using opencv algorithm.

This repository refer to the paper "Eigenfaces for recognition"[[1]](http://www.face-rec.org/algorithms/pca/jcn.pdf)  which is the first implementation of eigenvectors in recognizing faces.

The dataset[[2]](https://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html) that I used is a simple dataset provided by AT&T Laboratories Cambridge. 

Also, this repository is just for imporving my ability of implement the concept of only reading paper. So the code follows the steps that paper wrote. And because this is just for improving the ability of implementation, I just used the first 50 images (5 classes) to classify.

## Approach 

Pricipal component analysis (PCA)
Eigenvector and eigenvalue.
Detail is all in the paper.

I write the code to calculate eigenvectors in c++, but it is just too slow.

So~, because of the calculation spped of Matlab, I tend to save the image information by c++ first, and calculate eigenvectors by Matlab. After that, c++ read the eigenvectors results by txt and keep going on.




## GET started

Success in :

C++ 11, opencv (just for reading and diplaying), Microsoft visual studio 2015.

I do use opencv, but just for reading and diplay the image.

## Try 

First, extract the ATT.rar to the folder "Face_recognition".

And just run the main.cpp !

## Results

If everthing is fine.

First we can check the eigenface.

![fisherface](https://raw.githubusercontent.com/yoyotv/Face-detection-and-recognition/master/Face_recognition_fisher/For_matlab/fisher.jpg=112x92)

And have some test.
This is the result base on the first 6 fisher face.

![result](https://raw.githubusercontent.com/yoyotv/Face-detection-and-recognition/master/Face_recognition_fisher/fisher.JPG)



applying fisher If everthing is fine.

First we can check the fisherface.

![eigenface](https://raw.githubusercontent.com/yoyotv/Face-detection-and-recognition/master/Face_recognition/Eigenface.jpg)

And have some test.

![result](https://raw.githubusercontent.com/yoyotv/Face-detection-and-recognition/master/figures/result.JPG)


## References


[1] M. Turk, and A. Pentland, "Eigenfaces for Recognition," J. Cognitive Neuroscience, vol. 3, no. 1, 1991.

[2] "The Database of Faces," AT&T Laboratories Cambridge, (2002). [Online]. Available: http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html.
