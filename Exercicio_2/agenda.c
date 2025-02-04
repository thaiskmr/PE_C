#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

void inserir(Telefone **lista, char *ddd, char *numero) {
    Telefone *novo = (Telefone *)malloc(sizeof(Telefone));
    if (!novo) {
        printf("Erro de alocação\n");
        exit(1);
    }
    strcpy(novo->ddd, ddd);
    strcpy(novo->numero, numero);
    novo->prox = *lista;
    *lista = novo;
}

void remover(Telefone **lista, char *ddd, char *numero) {
    Telefone *atual = *lista, *anterior = NULL;
    while (atual) {
        if (strcmp(atual->ddd, ddd) == 0 && strcmp(atual->numero, numero) == 0) {
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
        strcpy(vetor[i].ddd, lista->ddd);
        strcpy(vetor[i].numero, lista->numero);
        lista = lista->prox;
    }
    return vetor;
}

int comparar(const void *a, const void *b) {
    Telefone *t1 = (Telefone *)a;
    Telefone *t2 = (Telefone *)b;
    int cmpDDD = strcmp(t1->ddd, t2->ddd);
    if (cmpDDD != 0)
        return cmpDDD;
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
        fprintf(arquivo, "%s\n%s\n", vetor[i].ddd, vetor[i].numero);
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