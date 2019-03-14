import os
import numpy as np
from PIL import Image

#This is used for displaying the image for double checking the input data.
#Remember to scale to 0~255!
#Or just use Matlab, it easier!

q=open("test.txt")

w=q.readlines()


q=np.zeros((10304,1))

for i in range(10304):
  q[i]=w[i]

print q.shape


#Use A or B
#A====={
#a=q.reshape((112,92))
#}
#B====={
a=np.empty((112,92))
print a.shape

d=0

for i in range(112):
  for j in range(92):
    a[i][j]=q[d]
    a[i][j]=-1
    d=d+1
#}




i=Image.fromarray(a)
i.show()



