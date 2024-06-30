#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#define TAMANHO 500000

int primo(int n) {
    int i;
    for (i = 3; i < (int)(sqrt(n) + 1); i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    double t_inicial, t_final;
    int total = 0;
    int i, n;

    // Verifica o número de argumentos passados
    if (argc < 2) {
        printf("Entre com o valor do maior inteiro como parâmetro para o programa.\n");
        return 0;
    } else {
        n = strtol(argv[1], (char **) NULL, 10);
        num_threads = strtol(argv[2], (char **) NULL, 10);
    }

    // Registra o tempo inicial de execução do programa
    t_inicial = omp_get_wtime();

    // Inicializa a contagem de primos
    #pragma omp parallel for reduction(+:total) schedule(dynamic, TAMANHO)
    for (i = 3; i < n; i += 2) {
        if (primo(i)) {
            total++;
        }
    }

    // Registra o tempo final de execução
    t_final = omp_get_wtime();

    // Acrescenta o 2, que é primo
    total += 1;

    // Imprime o resultado
    printf("Quant. de primos entre 1 e %d: %d \n", n, total);
    printf("Tempo de execucao: %1.3f \n", t_final - t_inicial);

    return 0;
}
