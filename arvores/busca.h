#ifndef BUSCA_H
#define BUSCA_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

typedef struct filme {
	char frase[256];
	char filme[256];
	char ano[10];
	struct filme *prox;
} Filme;

typedef struct {
	char palavra[50];
	int frequencia;
	Filme *listaFilmes;
} Palavra;

typedef struct NO {
	Palavra info;
	struct NO *esq;
	struct NO *dir;
} NO;
typedef struct NO *ArvBin;

struct NO2 {
	Palavra info;
	int altura;
	struct NO2 *esq;
	struct NO2 *dir;
};
typedef struct NO2* ArvAVL;

int criarVetorDePalavra(char *frase, char *filme, char *ano, Palavra v[], int pos);
void InsertionSort(Palavra v[],int tam);
void imprimirVetorDePalavras(Palavra v[], int tam);
void BuscaBinaria(Palavra v[],char chave[], int ini,int fim);
ArvBin* criaArvoreBinaria();
int insereArvoreBinaria(ArvBin* raiz, Palavra valor);
void insercaoArvBin(ArvBin* raiz, Palavra v[], int tam);
int buscaArvoreBinaria(ArvBin *raiz, char valor[]);
ArvAVL* cria_ArvAVL();
int altura_NO(struct NO2* no);
int fatorBalanceamento_NO(struct NO2* no);
void RotacaoLL(ArvAVL *A);
void RotacaoRR(ArvAVL *A);
void RotacaoLR(ArvAVL *A);
void RotacaoRL(ArvAVL *A);
int insereNoArvAVLFrequencia(ArvAVL *raiz, Palavra valor);
void InsercaoArvAVLFreq(Palavra v[], ArvAVL *raiz, int tam);
int buscaArvAVL(ArvAVL *raiz, int valor);
int insereNoArvAVLPalavra(ArvAVL *raiz, Palavra valor);
void InsercaoArvAVLPalavra(Palavra v[], ArvAVL *raiz, int tam);
int buscaArvAVLPalavra(ArvAVL *raiz, char valor[]);
int arquivo(Palavra v[], char arq[]);

#endif
