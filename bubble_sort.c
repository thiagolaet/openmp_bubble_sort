#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Função para gerar um vetor de inteiros aleatórios de 0 até 999999
int* generate_random_array(int n) {
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000000;
    }
    return array;
}

void compare_exchange(int* arr, int i, int j) {
    if (arr[i] > arr[j]) {
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void parallel_odd_even_sort(int arr[], int n, int num_threads) {
    for( int i = 0; i < n; i++ ) {
        int first = i % 2;
        #pragma omp parallel for
        for(int j = first; j < n-1; j += 2) {
            compare_exchange(arr, j, j+1);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <n> <num_threads>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);
    int num_threads = atoi(argv[2]);

    if (n <= 0) {
        printf("Erro: n deve ser positivo\n");
        return 1;
    }
    if (num_threads < 1) {
        printf("Erro: num_threads deve ser positivo\n");
        return 1;
    }

    srand(time(NULL));
    int *array = generate_random_array(n);
    printf("num_threads: %d | n: %d\n", num_threads, n);
    omp_set_num_threads(num_threads);

    double start = omp_get_wtime();
    parallel_odd_even_sort(array, n, num_threads);
    double end = omp_get_wtime();
    printf("Tempo: %.4f segundos\n", end - start);

    free(array);
    return 0;
}
