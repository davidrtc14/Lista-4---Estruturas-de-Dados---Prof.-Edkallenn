/*
** Função: Implementação de uma pilha de números reais
** Autor: David Ramalho Teixeira de Carvalho
** Data: 01/06/2024
** Observações: Este programa implementa uma pilha de números reais com operações de push, pop e verificação de pilha vazia.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct Nodo {
    double valor;
    struct Nodo* prox;
} Nodo;

typedef struct {
    Nodo* topo;
} Pilha;

void inicializar_pilha(Pilha* pilha) {
    pilha->topo = NULL;
}

int pilha_vazia(Pilha* pilha) {
    return pilha->topo == NULL;
}

void push(Pilha* pilha, double valor) {
    Nodo* novo_nodo = (Nodo*)malloc(sizeof(Nodo));
    if (novo_nodo == NULL) {
        printf("Erro de alocação de memória.\n");
        return;
    }
    novo_nodo->valor = valor;
    novo_nodo->prox = pilha->topo;
    pilha->topo = novo_nodo;
    printf("Elemento %.2f inserido na pilha.\n", valor);
}

void pop(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        printf("A pilha está vazia.\n");
        return;
    }
    Nodo* temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    printf("Elemento %.2f removido da pilha.\n", temp->valor);
    free(temp);
}

void exibir_pilha(Pilha* pilha) {
    if (pilha_vazia(pilha)) {
        printf("A pilha está vazia.\n");
        return;
    }
    Nodo* atual = pilha->topo;
    printf("Pilha: ");
    while (atual != NULL) {
        printf("%.2f ", atual->valor);
        atual = atual->prox;
    }
    printf("\n");
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Pilha pilha;
    inicializar_pilha(&pilha);

    int opcao;
    double valor;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir elemento (push)\n");
        printf("2. Retirar elemento (pop)\n");
        printf("3. Exibir pilha\n");
        printf("4. Verificar se a pilha está vazia\n");
        printf("5. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%lf", &valor);
                push(&pilha, valor);
                exibir_pilha(&pilha);
                break;
            case 2:
                pop(&pilha);
                exibir_pilha(&pilha);
                break;
            case 3:
                exibir_pilha(&pilha);
                break;
            case 4:
                if (pilha_vazia(&pilha)) {
                    printf("A pilha está vazia.\n");
                } else {
                    printf("A pilha não está vazia.\n");
                }
                break;
            case 5:
                printf("Encerrando o programa.\n");
                while (!pilha_vazia(&pilha)) {
                    pop(&pilha);
                }
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
