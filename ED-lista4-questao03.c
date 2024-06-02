/*
** Função: Gestão de perfil de saúde
** Autor: David Ramalho Teixeira de Carvalho
** Data: 01/06/2024
** Observações: Este programa gerencia perfis de saúde, calculando idade, IMC, frequência cardíaca máxima e ideal, e expectativa de vida.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    char nome_completo[80];
    char sexo;
    Data data_nascimento;
    float altura;
    float peso;
} perfil_saude;

int calcular_idade(Data data_nascimento) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    int idade = tm.tm_year + 1900 - data_nascimento.ano;
    if (tm.tm_mon + 1 < data_nascimento.mes || (tm.tm_mon + 1 == data_nascimento.mes && tm.tm_mday < data_nascimento.dia)) {
        idade--;
    }
    return idade;
}

float calcular_imc(float peso, float altura) {
    return peso / (altura * altura);
}

int calcular_freq_cardiaca_max(int idade) {
    return 220 - idade;
}

void calcular_freq_cardiaca_ideal(char sexo, int idade, int* freq_min, int* freq_max) {
    int freq_maxima = calcular_freq_cardiaca_max(idade);
    if (sexo == 'M' || sexo == 'm') {
        *freq_min = freq_maxima * 0.5;
        *freq_max = freq_maxima * 0.85;
    } else if (sexo == 'F' || sexo == 'f') {
        *freq_min = freq_maxima * 0.55;
        *freq_max = freq_maxima * 0.9;
    } else {
        *freq_min = 0;
        *freq_max = 0;
    }
}

int calcular_expectativa_vida(char sexo, int idade) {
    int expectativa = (sexo == 'M' || sexo == 'm') ? 76 : 82;
    return expectativa - idade;
}

void exibir_tabela_imc() {
    printf("\nTabela de valores do IMC:\n");
    printf("Menor que 18.5: Abaixo do peso\n");
    printf("Entre 18.5 e 24.9: Peso normal\n");
    printf("Entre 25 e 29.9: Sobrepeso\n");
    printf("Entre 30 e 34.9: Obesidade grau 1\n");
    printf("Entre 35 e 39.9: Obesidade grau 2\n");
    printf("Maior que 40: Obesidade grau 3\n");
}

void ler_perfil(perfil_saude* perfil) {
    printf("Nome Completo: ");
    fgets(perfil->nome_completo, sizeof(perfil->nome_completo), stdin);
    perfil->nome_completo[strcspn(perfil->nome_completo, "\n")] = '\0';

    printf("Sexo (M/F): ");
    scanf(" %c", &perfil->sexo);
    getchar(); 

    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &perfil->data_nascimento.dia, &perfil->data_nascimento.mes, &perfil->data_nascimento.ano);
    getchar(); 

    printf("Altura (em metros): ");
    scanf("%f", &perfil->altura);
    getchar(); 

    printf("Peso (em kg): ");
    scanf("%f", &perfil->peso);
    getchar(); 
}

void exibir_perfil(perfil_saude* perfil) {
    printf("\nNome Completo: %s\n", perfil->nome_completo);
    printf("Sexo: %c\n", perfil->sexo);
    printf("Data de Nascimento: %02d/%02d/%04d\n", perfil->data_nascimento.dia, perfil->data_nascimento.mes, perfil->data_nascimento.ano);
    printf("Altura: %.2f m\n", perfil->altura);
    printf("Peso: %.2f kg\n", perfil->peso);
}

int main() {
    setlocale(LC_ALL, "Portuguese");

    int n;
    printf("Digite o número de pessoas: ");
    scanf("%d", &n);
    getchar();

    perfil_saude* perfis = (perfil_saude*) malloc(n * sizeof(perfil_saude));

    for (int i = 0; i < n; i++) {
        printf("\n--- Perfil %d ---\n", i + 1);
        ler_perfil(&perfis[i]);
    }

    for (int i = 0; i < n; i++) {
        printf("\n--- Informações do Perfil %d ---\n", i + 1);
        exibir_perfil(&perfis[i]);

        int idade = calcular_idade(perfis[i].data_nascimento);
        printf("Idade: %d anos\n", idade);

        float imc = calcular_imc(perfis[i].peso, perfis[i].altura);
        printf("IMC: %.2f\n", imc);

        int freq_maxima = calcular_freq_cardiaca_max(idade);
        printf("Frequência Cardíaca Máxima: %d bpm\n", freq_maxima);

        int freq_min, freq_max;
        calcular_freq_cardiaca_ideal(perfis[i].sexo, idade, &freq_min, &freq_max);
        printf("Frequência Cardíaca Ideal: %d bpm - %d bpm\n", freq_min, freq_max);

        int expectativa = calcular_expectativa_vida(perfis[i].sexo, idade);
        printf("Expectativa de vida: %d anos\n", expectativa);

        exibir_tabela_imc();
    }

    free(perfis);

    return 0;
}
