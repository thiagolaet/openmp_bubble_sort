#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

// Função para gerar um vetor de inteiros aleatórios de 0 até 999999
int* generate_random_array(int n) {
    srand(time(NULL));
    int* array = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        array[i] = rand() % 1000000;
    }
    return array;
}

void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Bubble Sort sequencial
void sequential_bubble_sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

// Bubble Sort paralela
void parallel_bubble_sort() {
    printf("Versão paralela ainda não implementada!\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Uso: %s <n> <use_parallel>\n", argv[0]);
        printf("use_parallel: 0 = sequencial, 1 = paralelo\n");
        return 1;
    }
    int n = atoi(argv[1]);
    int use_parallel = atoi(argv[2]);

    if (n <= 0) {
        printf("Erro: n deve ser positivo\n");
        return 1;
    }
    if (use_parallel != 0 && use_parallel != 1) {
        printf("Erro: use_parallel deve ser 0 (sequencial) ou 1 (paralelo)\n");
        return 1;
    }

    int *array = generate_random_array(n);
    printf("Tamanho do vetor: %d\n", n);
    printf("Algoritmo: %s\n", use_parallel ? "Paralelo" : "Sequencial");

    if (use_parallel == 0) {
        // sequencial
        double start = omp_get_wtime();
        sequential_bubble_sort(array, n);
        double end = omp_get_wtime();
        printf("Tempo sequencial: %.4f segundos\n", end - start);
    } else {
        // paralelo
    }

    free(array);
    return 0;
}