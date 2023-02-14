#NOMBRE: DANIEL ANTONIO QUIHUIS HERNANDEZ
EXPEDIENTE: 215207132

#!/bin/sh
gcc -fopenmp maxgap_paralela1.c -o maxgap_paralela1 -lm
./maxgap_paralela1 1 200000

