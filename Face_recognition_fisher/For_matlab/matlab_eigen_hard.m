%Read all images which is in form (400*112*92)

clear all;clc;
clear all;
dataset=100/2;
classes=10/2;

a=fopen('Sb.txt','r');
s=fscanf(a,'%f',inf);
all=zeros(10304,10304);



%Calculate the matrix Sb
for i=1:classes

    q=s(1+10304*(i-1):10304*i);  %10304*1
    i
      all=all +q*q';
end

all=all.*10;

Sb=all;   %Obtain Sb !

fclose(a);
clear s;
clear q;

%Sb part


a=fopen('Sw.txt','r');
s=fscanf(a,'%f',inf);
all=zeros(10304,10304);


%Calculate the matrix Sw
for i=1:classes
    q=s(1+10304*(i-1):10304*i);  %10304*1
    i
      all=all +q*q';
end



Sw=all;   %Obtain Sb !

fclose(a);
clear s;
clear q;
%%%%%%%%%%%%%%%%%%%%%%%%

a=fopen('St.txt','r');
s=fscanf(a,'%f',inf);
all=zeros(10304,10304);


%Calculate the matrix Sw
for i=1:dataset
    q=s(1+10304*(i-1):10304*i);  %10304*1
    i
      all=all +q*q';
end
all=all./dataset;
St=all;
 [v,d]=eigs(St);  %Acquire the first 6 eigenvalues and eigenvectors.
%%%%%%%%%%%%%%%%%
%SS=inv(Sw)*Sb;
SS=inv(v'*Sw*v)*(v'*Sb*v);


 [vfld,d]=eigs(SS);  %Acquire the first 6 eigenvalues and eigenvectors.


 
 tem=vfld'*v';
 vopt=tem';
 
 
 vector1=vopt(:,1);
vector2=vopt(:,2);
vector3=vopt(:,3);
vector4=vopt(:,4);
vector5=vopt(:,5);
vector6=vopt(:,6);

save('eigenvalues.txt','d','-ascii')
save('eigenvector1.txt','vector1','-ascii')
save('eigenvector2.txt','vector2','-ascii')
save('eigenvector3.txt','vector3','-ascii')
save('eigenvector4.txt','vector4','-ascii')
save('eigenvector5.txt','vector5','-ascii')
 save('eigenvector6.txt','vector6','-ascii')
 
imshow(mat2gray(reshape(vector1,[92,112])))

fclose(a);








