/*
** Função: Simulação de lista de compras
** Autor: David Ramalho Teixeira de Carvalho
** Data: 01/06/2024
** Observações: Este programa simula uma lista de compras usando uma lista encadeada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_NOME 100

typedef struct Item {
    char nome[MAX_NOME];
    int quantidade;
    struct Item* prox;
} Item;

typedef struct Lista {
    Item* cabeca;
} Lista;

void inicializar_lista(Lista* lista) {
    lista->cabeca = NULL;
}

void inserir_item(Lista* lista, char* nome, int quantidade) {
    Item* novo_item = (Item*) malloc(sizeof(Item));
    if (novo_item == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    strcpy(novo_item->nome, nome);
    novo_item->quantidade = quantidade;
    novo_item->prox = lista->cabeca;
    lista->cabeca = novo_item;
}

void remover_item(Lista* lista, char* nome) {
    Item* atual = lista->cabeca;
    Item* anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nome) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Item não encontrado!\n");
        return;
    }

    if (anterior == NULL) {
        lista->cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Item removido com sucesso!\n");
}

void consultar_item(Lista* lista, char* nome) {
    Item* atual = lista->cabeca;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            printf("Item encontrado: %s, Quantidade: %d\n", atual->nome, atual->quantidade);
            return;
        }
        atual = atual->prox;
    }

    printf("Item não encontrado!\n");
}

void mostrar_lista(Lista* lista) {
    Item* atual = lista->cabeca;

    if (atual == NULL) {
        printf("A lista de compras está vazia.\n");
        return;
    }

    printf("Lista de compras:\n");
    while (atual != NULL) {
        printf("Produto: %s, Quantidade: %d\n", atual->nome, atual->quantidade);
        atual = atual->prox;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Lista lista;
    inicializar_lista(&lista);

    int opcao, quantidade;
    char nome[MAX_NOME];

    do {
        printf("\nEscolha uma operação:\n");
        printf("1 - Inserir item\n");
        printf("2 - Remover item\n");
        printf("3 - Consultar item\n");
        printf("4 - Mostrar lista\n");
        printf("5 - Encerrar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Nome do produto: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0'; 
                printf("Quantidade: ");
                scanf("%d", &quantidade);
                getchar();
                inserir_item(&lista, nome, quantidade);
                break;
            case 2:
                printf("Nome do produto a ser removido: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                remover_item(&lista, nome);
                break;
            case 3:
                printf("Nome do produto a ser consultado: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                consultar_item(&lista, nome);
                break;
            case 4:
                mostrar_lista(&lista);
                break;
            case 5:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 5);

    return 0;
}
