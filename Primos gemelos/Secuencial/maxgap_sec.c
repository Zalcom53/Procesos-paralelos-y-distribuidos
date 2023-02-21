// NOMBRE DEL ALUMNO:
// Quihuis Hernandez Daniel Antonio 
// EXPEDIENTE: 215207132



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

    /*printf("PRIMOS = [");
    for (i = 0; i < n-1; i++) 
        if (!marked[i]) 
            printf("%d,",i+2);
    printf("]");*/

    //  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■ Buscando el máximo GAP
    int maximoGAP = 0;
    int indice_primo = 1;     // primer primo es el 3
    for (i = 2; i < n-1; i++) // empieza en el 4
        if (!marked[i]){
            if( i - indice_primo > maximoGAP )
                maximoGAP = i - indice_primo;
            indice_primo = i;
        } 
    //  ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■

    gettimeofday(&fin,0); // toma de tiempo final

    long seconds = fin.tv_sec - inicio.tv_sec;
    long microseconds = fin.tv_usec - inicio.tv_usec;
    double diff_t = seconds + microseconds*1e-6;  

    printf ("\nHay %d números primos menores o iguales que %d\n", count, n);
    printf("\nEL maximo gap es %d\n", maximoGAP);
    printf("\nTiempo =  %.10f \n",diff_t);  
 
    return 0;
}
