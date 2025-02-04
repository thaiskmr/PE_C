#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agenda.h"

int main() {
    char arquivo_entrada[100], arquivo_saida[100];
    Telefone *lista = NULL;
    int n_operacoes;
    char ddd[3], numero[9], operacao;

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
        fscanf(arquivo, "%2s", ddd); 
        fscanf(arquivo, "%8s", numero); 
        
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