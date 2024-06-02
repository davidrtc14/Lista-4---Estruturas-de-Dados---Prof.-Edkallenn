/*
** Função: Classificação por Seleção
** Autor: David Ramalho Teixeira de Carvalho
** Data: 01/06/2024
** Observações: Este programa classifica elementos de um vetor em ordem crescente usando o algoritmo de seleção e testa a função com dados gerados aleatoriamente.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void selection_sort(int arr[], int n) {
    int i, j, min_idx, temp;
    
    for (i = 0; i < n-1; i++) {
        min_idx = i;
        for (j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }

        temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

void imprimir_vetor(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);

    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    srand(time(0));

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Vetor original:\n");
    imprimir_vetor(arr, n);

    selection_sort(arr, n);

    printf("Vetor ordenado:\n");
    imprimir_vetor(arr, n);

    free(arr);
    return 0;
}
