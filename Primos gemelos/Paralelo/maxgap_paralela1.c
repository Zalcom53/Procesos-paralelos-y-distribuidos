//%%writefile criba_1.c
// NOMBRE: DANIEL ANTONIO QUIHUIS HERNANDEZ
// EXPEDIENTE: 215207132

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>

#define BLOCK_LOW(id, p, n) ((id) * (n) / (p))
#define BLOCK_HIGH(id, p, n) (BLOCK_LOW((id) + 1, (p), (n)) - 1)
#define BLOCK_SIZE(id, p, n) (BLOCK_HIGH((id), (p), (n)) - BLOCK_LOW((id), (p), (n)) + 1)
#define MIN(i, j) (((i) < (j)) ? (i) : (j))
#define MAX(i, j) (((i) > (j)) ? (i) : (j))

int main(int argc, char *argv[]){
    int n, prime, i, count, index, numThreads, first;
    int ind_high, ind_low, chunk, id_thread;
    char  *marked;
    double start_time;
    double current_time;
    double elapsed_time; 

    numThreads = atoi(argv[1]);
    omp_set_num_threads (numThreads);

    start_time = omp_get_wtime();

    if (argc != 3) { printf ("Command line: %s <m>\n", argv[0]); exit (1);}

    n = atoi(argv[2]);
    marked = (char *) malloc (n); 
    if (marked == NULL) {printf ("Cannot allocate enough memory\n");exit (1);}    
    
    start_time = omp_get_wtime();
    #pragma omp parallel for firstprivate(n) shared(marked)
    for (i = 1; i < n; i++) 
        marked[i] = 0;
    
    marked[0] = 1; //<--- el uno está marcado desde el inicio pues no es el primer primo
   
    index = 0;
    prime = 2; // primer primo   
    do {  
        #pragma omp parallel private(i,first,id_thread,ind_low,ind_high) firstprivate(n,prime) shared(marked,numThreads)
        {            
            id_thread = omp_get_thread_num();
            ind_low   = BLOCK_LOW (id_thread, numThreads, n) + 1;
            ind_high  = BLOCK_HIGH(id_thread, numThreads, n) + 1;

            if ( prime * prime > ind_low )
                first = prime * prime - ind_low;
            else {
                if ( !( ind_low % prime ) ) 
                    first = 0;
                else 
                    first = prime - (ind_low % prime);
            }
            int inicio =  ind_low + first - 1;
            
            for ( i = inicio; i <= ind_high; i += prime )
                marked[i] = 1; // marcando a los múltiplos de k            
        }

        while (marked[++index]); // buscando el siguiente valor sin marcar
        prime = index + 1;       
    }while (prime * prime <= n); 
    
    // contando el número de valores sin marcar (el número de ceros en el arreglo marked)
    count = 0;
    #pragma omp parallel for firstprivate(n) reduction(+:count)	
    for (i = 0; i < n; i++) 
        if (!marked[i]) 
            count++;

    current_time = omp_get_wtime();
    elapsed_time = current_time - start_time;

  /*  printf("\nPRIMOS = [");
    for (i = 0; i < n; i++) 
        if (!marked[i]) 
            printf("%d,",i+1);
    printf("]");*/

     

    printf ("\nHay %d números primos menores o iguales que %d\n", count, n);
    printf("Tiempo= %.10f \n",elapsed_time);    
    return 0;
}
