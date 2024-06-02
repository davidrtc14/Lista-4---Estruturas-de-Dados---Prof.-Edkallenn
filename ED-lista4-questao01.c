/*
** Função: Gerir livros de uma biblioteca usando lista encadeada
** Autor: David Ramalho Teixeira de Carvalho
** Data: 01/06/2024
** Observações: Este programa gerencia uma base de dados de livros de uma biblioteca usando listas encadeadas.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Livro {
    char autor[50];
    char titulo[50];
    char editora[50];
    int ano;
    struct Livro* prox;
} Livro;

Livro* criar_livro(char* autor, char* titulo, char* editora, int ano) {
    Livro* novo = (Livro*)malloc(sizeof(Livro));
    strcpy(novo->autor, autor);
    strcpy(novo->titulo, titulo);
    strcpy(novo->editora, editora);
    novo->ano = ano;
    novo->prox = NULL;
    return novo;
}

void inserir_livro(Livro** cabeca, char* autor, char* titulo, char* editora, int ano) {
    Livro* novo = criar_livro(autor, titulo, editora, ano);
    if (*cabeca == NULL || strcmp((*cabeca)->titulo, titulo) > 0) {
        novo->prox = *cabeca;
        *cabeca = novo;
    } else {
        Livro* atual = *cabeca;
        while (atual->prox != NULL && strcmp(atual->prox->titulo, titulo) < 0) {
            atual = atual->prox;
        }
        novo->prox = atual->prox;
        atual->prox = novo;
    }
}

void remover_livro(Livro** cabeca, char* titulo) {
    Livro* atual = *cabeca;
    Livro* anterior = NULL;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Livro não encontrado.\n");
        return;
    }

    if (anterior == NULL) {
        *cabeca = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    free(atual);
    printf("Livro removido com sucesso.\n");
}

void alterar_livro(Livro* cabeca, char* titulo) {
    Livro* atual = cabeca;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Livro não encontrado.\n");
        return;
    }

    printf("Digite o novo autor: ");
    fgets(atual->autor, 50, stdin);
    atual->autor[strcspn(atual->autor, "\n")] = '\0';

    printf("Digite o novo título: ");
    fgets(atual->titulo, 50, stdin);
    atual->titulo[strcspn(atual->titulo, "\n")] = '\0';

    printf("Digite a nova editora: ");
    fgets(atual->editora, 50, stdin);
    atual->editora[strcspn(atual->editora, "\n")] = '\0';

    printf("Digite o novo ano: ");
    scanf("%d", &atual->ano);
    getchar();

    printf("Livro alterado com sucesso.\n");
}

void buscar_por_titulo(Livro* cabeca, char* titulo) {
    Livro* atual = cabeca;

    while (atual != NULL && strcmp(atual->titulo, titulo) != 0) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        printf("Livro não encontrado.\n");
    } else {
        printf("Autor: %s\n", atual->autor);
        printf("Título: %s\n", atual->titulo);
        printf("Editora: %s\n", atual->editora);
        printf("Ano: %d\n", atual->ano);
    }
}

void buscar_por_autor(Livro* cabeca, char* autor) {
    Livro* atual = cabeca;
    int encontrado = 0;

    while (atual != NULL) {
        if (strcmp(atual->autor, autor) == 0) {
            printf("Autor: %s\n", atual->autor);
            printf("Título: %s\n", atual->titulo);
            printf("Editora: %s\n", atual->editora);
            printf("Ano: %d\n\n", atual->ano);
            encontrado = 1;
        }
        atual = atual->prox;
    }

    if (!encontrado) {
        printf("Nenhum livro encontrado para o autor %s.\n", autor);
    }
}

void listar_livros(Livro* cabeca) {
    Livro* atual = cabeca;

    while (atual != NULL) {
        printf("Autor: %s\n", atual->autor);
        printf("Título: %s\n", atual->titulo);
        printf("Editora: %s\n", atual->editora);
        printf("Ano: %d\n\n", atual->ano);
        atual = atual->prox;
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    Livro* biblioteca = NULL;
    int opcao;
    char autor[50], titulo[50], editora[50];
    int ano;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Inserir livro\n");
        printf("2. Remover livro\n");
        printf("3. Alterar livro\n");
        printf("4. Buscar livro por título\n");
        printf("5. Buscar livro por autor\n");
        printf("6. Listar todos os livros\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Digite o autor: ");
                fgets(autor, 50, stdin);
                autor[strcspn(autor, "\n")] = '\0';

                printf("Digite o título: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                printf("Digite a editora: ");
                fgets(editora, 50, stdin);
                editora[strcspn(editora, "\n")] = '\0';

                printf("Digite o ano: ");
                scanf("%d", &ano);
                getchar();

                inserir_livro(&biblioteca, autor, titulo, editora, ano);
                printf("Livro inserido com sucesso.\n");
                break;
            case 2:
                printf("Digite o título do livro a ser removido: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                remover_livro(&biblioteca, titulo);
                break;
            case 3:
                printf("Digite o título do livro a ser alterado: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                alterar_livro(biblioteca, titulo);
                break;
            case 4:
                printf("Digite o título do livro a ser buscado: ");
                fgets(titulo, 50, stdin);
                titulo[strcspn(titulo, "\n")] = '\0';

                buscar_por_titulo(biblioteca, titulo);
                break;
            case 5:
                printf("Digite o nome do autor a ser buscado: ");
                fgets(autor, 50, stdin);
                autor[strcspn(autor, "\n")] = '\0';

                buscar_por_autor(biblioteca, autor);
                break;
            case 6:
                listar_livros(biblioteca);
                break;
            case 7:
                printf("Encerrando o programa.\n");
                while (biblioteca != NULL) {
                    Livro* temp = biblioteca;
                    biblioteca = biblioteca->prox;
                    free(temp);
                }
                return 0;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    }

    return 0;
}
