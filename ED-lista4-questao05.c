#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define MAX_DESC 100

typedef struct Processo {
    int identificador;
    char descricao[MAX_DESC];
    struct Processo* prox;
} Processo;

typedef struct Pilha {
    Processo* topo;
} Pilha;

void inicializar_pilha(Pilha* p) {
    p->topo = NULL;
}

int pilha_vazia(Pilha* p) {
    return p->topo == NULL;
}

void push(Pilha* p, int id, char* desc) {
    Processo* novo_processo = (Processo*) malloc(sizeof(Processo));
    if (novo_processo == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }
    novo_processo->identificador = id;
    strcpy(novo_processo->descricao, desc);
    novo_processo->prox = p->topo;
    p->topo = novo_processo;
}

void pop(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("Pilha vazia\n");
        return;
    }
    Processo* temp = p->topo;
    printf("Removido o processo #%d - %s\n", temp->identificador, temp->descricao);
    p->topo = p->topo->prox;
    free(temp);
}

void mostrar_pilha(Pilha* p) {
    if (pilha_vazia(p)) {
        printf("Pilha vazia\n");
        return;
    }
    Processo* atual = p->topo;
    printf("Estado atual da pilha:\n");
    while (atual != NULL) {
        printf("Processo #%d - %s\n", atual->identificador, atual->descricao);
        atual = atual->prox;
    }
}

void esvaziar_pilha(Pilha* p) {
    while (!pilha_vazia(p)) {
        pop(p);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Pilha p;
    inicializar_pilha(&p);

    int opcao, id;
    char descricao[MAX_DESC];

    do {
        printf("\nEscolha uma operação:\n");
        printf("1 - Incluir um processo\n");
        printf("2 - Retirar um processo\n");
        printf("3 - Encerrar\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Identificador do processo: ");
                scanf("%d", &id);
                getchar(); 
                printf("Descrição do processo: ");
                fgets(descricao, MAX_DESC, stdin);
                descricao[strcspn(descricao, "\n")] = '\0'; 
                push(&p, id, descricao);
                mostrar_pilha(&p);
                break;
            case 2:
                pop(&p);
                mostrar_pilha(&p);
                break;
            case 3:
                esvaziar_pilha(&p);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    return 0;
}
