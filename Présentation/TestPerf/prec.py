import sys
import numpy as np;

val_read = [];
with open(sys.argv[1], 'r') as f:
    d = f.readlines()
    for i in d:
        val_read.append((int)(i)) 

#print("longueur tableau lu ", len(val_read));
#print(val_read[15], val_read[15]+2);

val_temoin = 220;

dif_squared = 0;
error_counter = 1;

for i in range(1000):
	if ((val_read[i]==-1) or (val_read[i] < val_temoin-0.1*val_temoin) or (val_read[i] > val_temoin+0.1*val_temoin)):
		error_counter += 1;
	else:
		dif_squared += (val_read[i]-val_temoin)*(val_read[i]-val_temoin);
		
	
print("Nombre de -1 : ", error_counter - 1);
print("Ecart a la valeur : " ,dif_squared/(1000 - error_counter))