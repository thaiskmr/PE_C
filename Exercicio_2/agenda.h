#ifndef AGENDA_H
#define AGENDA_H

typedef struct Telefone {
    char ddd[3];
    char numero[9]; 
    struct Telefone *prox;
} Telefone;

void inserir(Telefone **lista, char *ddd, char *numero);
void remover(Telefone **lista, char *ddd, char *numero);
int contar_elementos(Telefone *lista);
Telefone *copiar_para_vetor(Telefone *lista, int tamanho);
void ordenar_telefones(Telefone *vetor, int tamanho);
void salvar_arquivo(Telefone *vetor, int tamanho, char *nome_saida);
void liberar_lista(Telefone *lista);
void liberar_vetor(Telefone *vetor);

#endif