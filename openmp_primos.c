#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>


int primo (long int n) { /* mpi_primos.c  */
	int i;
       
	for (i = 3; i < (int)(sqrt(n) + 1); i+=2) {
			if(n%i == 0) return 0;
	}
	return 1;
}

int main(int argc, char* argv[]) {
    double t_inicial, t_final;
    long int i, n, n_threads;
    int cont = 0;

    if (argc < 2) {
        // printf("Valor inválido! Entre com um valor do maior inteiro\n");
       	return 0;
    }else {
        n = strtol(argv[1], (char **) NULL, 10);
        n_threads = strtol(argv[2], (char **) NULL, 10);
    }

    t_inicial = omp_get_wtime();

    #pragma omp parallel for shared(cont) num_threads(n_threads)
    for (i = 2; i <= n; i += 2) {	
        if(primo(i) == 1){
            // printf("achou primo: %d / thread: %d\n", i, omp_get_thread_num());
            cont++;   
        }
    }

    t_final = omp_get_wtime();
    double time = t_final - t_inicial;

    // printf("quantidade total de primos: %d\n", cont);
    // printf("tempo decorrido: %f\n", t_final - t_inicial);
    printf("Naive,%ld,%.3f,%ld\n",n_threads,time,n);

    return 0;
}