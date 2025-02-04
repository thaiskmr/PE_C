#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

void inserir(Telefone **lista, int ddd, char *numero) {
    Telefone *novo = (Telefone *)malloc(sizeof(Telefone));
    if (!novo) {
        printf("Erro de alocação\n");
        exit(1);
    }
    novo->ddd = ddd;
    strcpy(novo->numero, numero);
    novo->prox = *lista;
    *lista = novo;
}

void remover(Telefone **lista, int ddd, char *numero) {
    Telefone *atual = *lista, *anterior = NULL;
    while (atual) {
        if (atual->ddd == ddd && strcmp(atual->numero, numero) == 0) {
            if (anterior)
                anterior->prox = atual->prox;
            else
                *lista = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

int contar_elementos(Telefone *lista) {
    int count = 0;
    while (lista) {
        count++;
        lista = lista->prox;
    }
    return count;
}

Telefone *copiar_para_vetor(Telefone *lista, int tamanho) {
    Telefone *vetor = (Telefone *)malloc(tamanho * sizeof(Telefone));
    if (!vetor) {
        printf("Erro de alocação\n");
        exit(1);
    }
    for (int i = 0; lista; i++) {
        vetor[i] = *lista;
        lista = lista->prox;
    }
    return vetor;
}

int comparar(const void *a, const void *b) {
    Telefone *t1 = (Telefone *)a;
    Telefone *t2 = (Telefone *)b;
    if (t1->ddd != t2->ddd)
        return t1->ddd - t2->ddd;
    return strcmp(t1->numero, t2->numero);
}

void ordenar_telefones(Telefone *vetor, int tamanho) {
    qsort(vetor, tamanho, sizeof(Telefone), comparar);
}

void salvar_arquivo(Telefone *vetor, int tamanho, char *nome_saida) {
    FILE *arquivo = fopen(nome_saida, "w");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de saída\n");
        exit(1);
    }
    fprintf(arquivo, "%d\n", tamanho);
    for (int i = 0; i < tamanho; i++)
        fprintf(arquivo, "%d\n%s\n", vetor[i].ddd, vetor[i].numero);
    fclose(arquivo);
}

void liberar_lista(Telefone *lista) {
    while (lista) {
        Telefone *temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

void liberar_vetor(Telefone *vetor) {
    free(vetor);
}

int main() {
    char arquivo_entrada[100], arquivo_saida[100];
    Telefone *lista = NULL;
    int n_operacoes, ddd;
    char numero[9], operacao;

    scanf("%s", arquivo_entrada);
    scanf("%s", arquivo_saida);

    FILE *arquivo = fopen(arquivo_entrada, "r");
    if (!arquivo) {
        printf("Erro ao abrir arquivo de entrada\n");
        return 1;
    }

    fscanf(arquivo, "%d", &n_operacoes);

    for (int i = 0; i < n_operacoes; i++) {
        fscanf(arquivo, " %c", &operacao);
        fscanf(arquivo, "%d", &ddd);
        fscanf(arquivo, "%s", numero);

        if (operacao == 'I') {
            inserir(&lista, ddd, numero);
        } else if (operacao == 'R') {
            remover(&lista, ddd, numero);
        }
    }

    fclose(arquivo);

    int tamanho = contar_elementos(lista);
    Telefone *vetor = copiar_para_vetor(lista, tamanho);
    ordenar_telefones(vetor, tamanho);

    salvar_arquivo(vetor, tamanho, arquivo_saida);

    liberar_lista(lista);
    liberar_vetor(vetor);

    return 0;
}
