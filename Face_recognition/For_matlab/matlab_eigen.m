%Read all images which is in form (400*112*92)

clear all;clc;
a=fopen('test2.txt','r');
s=fscanf(a,'%f',inf);
all=zeros(10304,10304);
%Calculate the matrix A
for i=1:400
    q=s(1+10304*(i-1):10304*i);  %10304*1
    i
      all=all +q*q';
end

all=all./400;

A=all;   %Obtain A !

 [v,d]=eigs(A);  %Acquire the first 6 eigenvalues and eigenvectors.

vector1=v(:,1);
vector2=v(:,2);
vector3=v(:,3);
vector4=v(:,4);
vector5=v(:,5);
vector6=v(:,6);

save('eigenvalues.txt','d','-ascii')
save('eigenvector1.txt','vector1','-ascii')
save('eigenvector1.txt','vector2','-ascii')
save('eigenvector1.txt','vector3','-ascii')
save('eigenvector1.txt','vector4','-ascii')
save('eigenvector1.txt','vector5','-ascii')
save('eigenvector1.txt','vector6','-ascii')





