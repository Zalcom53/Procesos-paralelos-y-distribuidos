%%writefile criba_sec.c
/*
  Criba de Eratóthenes
  programado por : José Alberto Leyva
  15 de octubre de 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char *argv[]){
    int n, k, i, count, index = 0;
    char  *marked;
  
    struct timeval inicio, fin;
    

    if (argc != 2) { printf ("Command line: %s <m>\n", argv[0]); exit (1);}

    n = atoi(argv[1]);
    marked = (char *) malloc (n-1); // para quitar el 1
    if (marked == NULL) {printf ("Cannot allocate enough memory\n");exit (1);}
    
    gettimeofday(&inicio,0); // toma de tiempo inicial
    for (i = 0; i < n-1; i++) 
        marked[i] = 0;
   
    k = 2; // primer primo   
    do {
        for (i = k*k - 2; i < n-1; i += k)
            marked[i] = 1; // marcando a los múltiplos de k
       
        while (marked[++index]); // buscando el siguiente valor sin marcar
        k = index + 2;       
    }while (k * k <= n); 
    
    // contando el número de valores sin marcar (el número de ceros en el arreglo marked)
    count = 0;
    for (i = 0; i < n-1; i++) 
        if (!marked[i]) 
            count++;
 
    gettimeofday(&fin,0); // toma de tiempo final

    printf("PRIMOS = [");
    for (i = 0; i < n-1; i++) 
        if (!marked[i]) 
            printf("%d,",i+2);
    printf("]");

    long seconds = fin.tv_sec - inicio.tv_sec;
    long microseconds = fin.tv_usec - inicio.tv_usec;
    double diff_t = seconds + microseconds*1e-6;  

    printf ("Hay %d números primos menores o iguales que %d\n", count, n);
    printf("\nTiempo =  %.10f \n",diff_t);  
 
    return 0;
}