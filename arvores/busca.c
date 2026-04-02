#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "busca.h"


// Funcao que extrai palavras de uma frase e atualiza o vetor de palavras
int criarVetorDePalavra(char *frase, char *filme, char *ano, Palavra v[], int pos) {
	char aux[1000];// palavra temporaria
	int in=0;

	// Converte todos os caracteres da frase para minusculo
	for (int i = 0; i < strlen(frase); i++) frase[i] = tolower(frase[i]);

	for(int i=0; i<strlen(frase); i++) {
		// Constroi palavras com letras de a-z
		if(frase[i]>='a' && frase[i]<='z') {
			aux[in]=frase[i];
			in++;
		} else {
			// Se a palavra tiver mais de 3 letras, adiciona ou atualiza no vetor
			if(strlen(aux)>3) {
				int flag=0;
				for(int k=0; k<pos; k++) {
					if(strcmp(v[k].palavra, aux)==0) {
						// Palavra ja existe, incrementa frequencia e adiciona nova citacao
						v[k].frequencia++;
						Filme *novoFilme = (Filme *)malloc(sizeof(Filme));
						strcpy(novoFilme->frase, frase);
						strcpy(novoFilme->filme, filme);
						strcpy(novoFilme->ano, ano);
						novoFilme->prox = v[k].listaFilmes;
						v[k].listaFilmes = novoFilme;
						flag = 1;
						break;
					}
				}
				// Palavra nova, insere no vetor
				if(flag==0) {
					Filme *novoFilme = (Filme *)malloc(sizeof(Filme));
					strcpy(v[pos].palavra, aux);
					v[pos].frequencia = 1;
					strcpy(novoFilme->frase, frase);
					strcpy(novoFilme->filme, filme);
					strcpy(novoFilme->ano, ano);
					novoFilme->prox = v[pos].listaFilmes;
					v[pos].listaFilmes = novoFilme;
					pos++;
				}
			}
			// Limpa auxiliar
			for(int j=0; j<100; j++)aux[j]='\0';
			in=0;
		}
	}
	return pos;
}

void InsertionSort(Palavra v[],int tam) {
	int i,j;
	Palavra temp;
	for(i=1; i<tam; i++) {
		temp=v[i];
		for(j=i-1; j>=0 && strcmp(v[j].palavra,temp.palavra)>0; j--) {
			v[j + 1] = v[j];
		}
		v[j + 1] = temp;
	}
}

void imprimirVetorDePalavras(Palavra v[], int tam) {

	for(int i=0; i<tam; i++) {
		printf("\nPalavra: %s\nFrequencia: %d\n", v[i].palavra, v[i].frequencia);
		Filme *aux=v[i].listaFilmes;
		while(aux!=NULL) {
			printf("Citacao: %s\nFilme: %s\nAno: %s\n", aux->frase, aux->filme, aux->ano);
			aux=aux->prox;
		}
	}
}


//Busca binaria recursiva no vetor ordenado de palavras
void BuscaBinaria(Palavra v[],char chave[], int ini,int fim) {
	// Caso base: se o indice inicial ultrapassou o final, a palavra nao foi encontrada
	if(ini>fim) {
		printf("Palavra nao encontrada\n");
		return;
	}

	// Calcula o indice do meio do vetor
	int meio=ini+(fim-ini)/2;

	// Compara a palavra do meio com a chave buscada
	if(strcmp(v[meio].palavra,chave)==0) {
		// Palavra encontrada, imprime a palavra e sua frequencia
		printf("Palavra encontrada: %s \nFrequencia: %d\n",v[meio].palavra,v[meio].frequencia);
		Filme *aux=v[meio].listaFilmes;
		while (aux != NULL) {
			// Imprime detalhes da citacao, filme e ano
			printf("\nCitacao: %s\n  Filme: %s\n  Ano: %s\n", aux->frase, aux->filme, aux->ano);
			aux = aux->prox; // Avanca para o proximo da lista
		}
	} else if(strcmp(v[meio].palavra,chave)>0) {
		// Se a palavra do meio for maior que a chave, busca na metade esquerda
		BuscaBinaria(v,chave,ini,meio-1);
	} else {
		// Se a palavra do meio for menor que a chave, busca na metade direita
		BuscaBinaria(v,chave,meio+1,fim);
	}

}



// Funcao para criar uma Arvore Binaria (retorna um ponteiro para a raiz da Arvore)
ArvBin* criaArvoreBinaria() {
	// Aloca memoria para o ponteiro da raiz
	ArvBin* raiz = (ArvBin*) malloc(sizeof(ArvBin));
	if(raiz != NULL)
		*raiz = NULL;// Inicializa como Arvore vazia
	return raiz;
}

// Funcao para inserir um no na Arvore Binaria
int insereArvoreBinaria(ArvBin* raiz, Palavra valor) {
	if(raiz == NULL)
		return 0;// Arvore nao existe

	// Aloca memoria para o novo no
	struct NO* novo;
	novo = (struct NO*) malloc(sizeof(struct NO));
	if(novo == NULL)
		return 0;

	// Inicializa os campos do novo no
	novo->info = valor;
	novo->dir = NULL;
	novo->esq = NULL;

	// Se a Arvore estiver vazia, o novo no vira a raiz
	if(*raiz == NULL)
		*raiz = novo;
	else {
		// Senao, percorre a Arvore para achar a posicao correta
		struct NO* atual = *raiz;
		struct NO* ant = NULL;
		while(atual != NULL) {
			ant = atual;

			// Se a palavra for maior, vai para a direita
			if(strcmp(valor.palavra,atual->info.palavra)>0)
				atual = atual->dir;
			// Senao, vai para a esquerda
			else
				atual = atual->esq;
		}

		// Insere o novo no como filho do no anterior
		if(strcmp(valor.palavra,ant->info.palavra)>0)
			ant->dir = novo;
		else
			ant->esq = novo;
	}
	return 1;
}

// Funcao para inserir varios elementos do vetor na Arvore
void insercaoArvBin(ArvBin* raiz, Palavra v[], int tam) {
	for(int i=0; i<tam; i++) {
		insereArvoreBinaria(raiz, v[i]); // Insere cada palavra individualmente
	}
}

// Funcao para buscar uma palavra na Arvore Binaria
int buscaArvoreBinaria(ArvBin *raiz, char valor[]) {
	if(raiz == NULL)
		return 0; // Arvore nao existe

	struct NO* atual = *raiz;

	// Percorre a Arvore buscando a palavra
	while(atual != NULL) {
		if(strcmp(valor, atual->info.palavra)==0) {
			// Palavra encontrada, imprime os dados
			printf("Palavra encontrada: %s \nFrequencia: %d\n",atual->info.palavra,atual->info.frequencia);
			Filme *aux=atual->info.listaFilmes;

			// Mostra todas as citacoes associadas a essa palavra
			while (aux != NULL) {
				printf("\nCitacao: %s\n  Filme: %s\n  Ano: %s\n", aux->frase, aux->filme, aux->ano);
				aux = aux->prox;// Avanca na lista
			}
			return 1;// Palavra encontrada
		}

		// Decide se vai para direita ou esquerda na Arvore
		if(strcmp(valor, atual->info.palavra)>0)
			atual = atual->dir;
		else
			atual = atual->esq;
	}

	// Palavra nao encontrada
	printf("Palavra nao encontrada!\n");
	return 0;
}

//Funcoes da arvore AVL
ArvAVL* cria_ArvAVL() {
	ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
	if(raiz != NULL)
		*raiz = NULL; // Inicializa a Arvore como vazia
	return raiz;
}

// Funcao que retorna a altura de um no (util para calcular balanceamento)
int altura_NO(struct NO2* no) {
	if(no == NULL)
		return -1; // no nulo tem altura -1
	else
		return no->altura; // Retorna altura armazenada no no
}

// Funcao que calcula o fator de balanceamento de um no (diferenca entre subArvores)
int fatorBalanceamento_NO(struct NO2* no) {
	return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

// Funcao auxiliar para retornar o maior entre dois numeros
int maior(int x, int y) {
	if(x > y)
		return x;
	else
		return y;
}

// Rotacao simples a direita (caso LL - insercao na subArvore esquerda-esquerda)
void RotacaoLL(ArvAVL *A) { //LL
	//printf("RotacaoLL\n");
	struct NO2 *B;
	B = (*A)->esq;
	(*A)->esq = B->dir;
	B->dir = *A;

	// Atualiza as alturas dos nos apos a rotacao
	(*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
	B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;

	*A = B; // B vira a nova raiz da subArvore
}

// Rotacao simples a esquerda (caso RR - insercao na subArvore direita-direita)
void RotacaoRR(ArvAVL *A) { //RR
	//printf("RotacaoRR\n");
	struct NO2 *B;
	B = (*A)->dir;
	(*A)->dir = B->esq;
	B->esq = (*A);

	// Atualiza as alturas
	(*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
	B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;

	(*A) = B; // B vira a nova raiz da subArvore
}

// Rotacao dupla esquerda-direita (caso LR - insercao na subArvore esquerda-direita)
void RotacaoLR(ArvAVL *A) { //LR
	RotacaoRR(&(*A)->esq);
	RotacaoLL(A);
}

// Rotacao dupla direita-esquerda (caso RL - insercao na subArvore direita-esquerda)
void RotacaoRL(ArvAVL *A) { //RL
	RotacaoLL(&(*A)->dir);
	RotacaoRR(A);
}

// Funcao para inserir um no na Arvore AVL com base na frequencia da palavra
int insereNoArvAVLFrequencia(ArvAVL *raiz, Palavra valor) {
	int res;

	// Caso base: Arvore vazia, cria novo no
	if (*raiz == NULL) {
		struct NO2 *novo;
		novo = (struct NO2*)malloc(sizeof(struct NO2));
		if (novo == NULL)
			return 0;

		novo->info = valor;
		novo->altura = 0;
		novo->esq = NULL;
		novo->dir = NULL;
		*raiz = novo;
		return 1;
	}

	struct NO2 *atual = *raiz;

	// Se a nova palavra tem frequencia menor OU (mesma frequencia e ordem alfabC)tica menor)
	if (valor.frequencia < atual->info.frequencia ||
	        (valor.frequencia == atual->info.frequencia && strcmp(valor.palavra, atual->info.palavra) < 0)) {

		// Insere a esquerda
		if ((res = insereNoArvAVLFrequencia(&(atual->esq), valor)) == 1) {
			// Verifica se precisa balancear
			if (fatorBalanceamento_NO(atual) >= 2) {
				if (valor.frequencia < (*raiz)->esq->info.frequencia ||
				        (valor.frequencia == (*raiz)->esq->info.frequencia &&
				         strcmp(valor.palavra, (*raiz)->esq->info.palavra) < 0)) {
					// Rotacao simples a direita
					RotacaoLL(raiz);
				} else {
					// Rotacao dupla: esquerda-direita
					RotacaoLR(raiz);
				}
			}
		}

		// Se a nova palavra tem frequencia maior OU (mesma frequencia e ordem alfabC)tica maior)
	} else if (valor.frequencia > atual->info.frequencia ||
	           (valor.frequencia == atual->info.frequencia && strcmp(valor.palavra, atual->info.palavra) > 0)) {

		// Insere a direita
		if ((res = insereNoArvAVLFrequencia(&(atual->dir), valor)) == 1) {
			// Verifica se precisa balancear
			if (fatorBalanceamento_NO(atual) >= 2) {
				if ((*raiz)->dir->info.frequencia < valor.frequencia ||
				        ((*raiz)->dir->info.frequencia == valor.frequencia &&
				         strcmp((*raiz)->dir->info.palavra, valor.palavra) < 0)) {
					// Rotacao simples a esquerda
					RotacaoRR(raiz);
				} else {
					// Rotacao dupla: direita-esquerda
					RotacaoRL(raiz);
				}
			}
		}

	} else {
		// Palavra com frequencia ja existe nao insere duplicados
		printf("Valor duplicado!!\n");
		return 0;
	}

	// Atualiza a altura do no atual apos possC-vel insercao
	atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
	return res;
}

// Funcao para inserir todas as palavras do vetor 'v' na Arvore AVL
void InsercaoArvAVLFreq(Palavra v[], ArvAVL *raiz, int tam) {
	for (int i = 0; i < tam; i++) {
		insereNoArvAVLFrequencia(raiz, v[i]);
	}
}

// Funcao de busca por frequencia na Arvore AVL
int buscaArvAVL(ArvAVL *raiz, int valor) {
	int flag = 0;
	struct NO2 *atual = *raiz;

	if (atual != NULL) {
		// Se encontrar a frequencia exata
		if (atual->info.frequencia == valor) {
			printf("\nFrequencia encontrada\nPalavra: %s", atual->info.palavra);

			// Percorre lista de filmes associados a palavra
			Filme *aux = atual->info.listaFilmes;
			while (aux != NULL) {
				printf("\nCitacao: %s\n  Filme: %s\n  Ano: %s\n", aux->frase, aux->filme, aux->ano);
				aux = aux->prox;
			}
			flag = 1;
		}

		// Continua busca a esquerda
		if (buscaArvAVL(&(atual->esq), valor)) {
			flag = 1;
		}

		// Continua busca a direita
		if (buscaArvAVL(&(atual->dir), valor)) {
			flag = 1;
		}
	}

	return flag; // Retorna 1 se encontrou, 0 caso contrC!rio
}


// Funcao para inserir um no na Arvore AVL com base na palavra
int insereNoArvAVLPalavra(ArvAVL *raiz, Palavra valor) {
	int res;

	// Se o no atual for NULL, cria um novo no
	if(*raiz == NULL) {
		struct NO2 *novo;
		novo = (struct NO2*)malloc(sizeof(struct NO2));
		if(novo == NULL)
			return 0; // Erro ao alocar memoria

		novo->info = valor;  // Atribui o valor ao novo no
		novo->altura = 0;    // Define a altura inicial do no como 0
		novo->esq = NULL;    // Inicializa a subArvore esquerda como NULL
		novo->dir = NULL;    // Inicializa a subArvore direita como NULL
		*raiz = novo;        // Define o novo no como raiz
		return 1;            // Insercao bem-sucedida
	}

	// Se o no nao for NULL, comeca a busca pela posicao correta
	struct NO2 *atual = *raiz;

	// Se a palavra a ser inserida for menor que a do no atual, insere na subArvore esquerda
	if(strcmp(valor.palavra, atual->info.palavra) < 0) {

		if((res = insereNoArvAVLPalavra(&(atual->esq), valor)) == 1) {
			// Se a insercao foi bem-sucedida, verifica o fator de balanceamento
			if(fatorBalanceamento_NO(atual) >= 2) {
				// Se o fator de balanceamento for 2 ou maior, faz a rotacao adequada
				if(strcmp(valor.palavra, (*raiz)->esq->info.palavra) < 0) {
					RotacaoLL(raiz);  // Caso de rotacao a esquerda
				} else {
					RotacaoLR(raiz);  // Caso de rotacao a esquerda-direita
				}
			}
		}

	} else if(strcmp(valor.palavra, atual->info.palavra) > 0) {
		// Se a palavra a ser inserida for maior que a do no atual, insere na subArvore direita
		if((res = insereNoArvAVLPalavra(&(atual->dir), valor)) == 1) {
			// Se a insercao foi bem-sucedida, verifica o fator de balanceamento
			if(fatorBalanceamento_NO(atual) >= 2) {
				// Se o fator de balanceamento for 2 ou maior, faz a rotacao adequada
				if(strcmp((*raiz)->dir->info.palavra, valor.palavra) < 0) {
					RotacaoRR(raiz);  // Caso de rotacao a direita
				} else {
					RotacaoRL(raiz);  // Caso de rotacao a direita-esquerda
				}
			}
		}

	} else {
		// Se a palavra ja existir na Arvore, nao insere (evita duplicatas)
		printf("Valor duplicado!!\n");
		return 0;
	}

	// Atualiza a altura do no apos a insercao
	atual->altura = maior(altura_NO(atual->esq), altura_NO(atual->dir)) + 1;
	return res;
}

// Funcao para inserir um array de palavras na Arvore AVL
void InsercaoArvAVLPalavra(Palavra v[], ArvAVL *raiz, int tam) {
	for(int i = 0; i < tam; i++) {
		// Insere cada palavra no array na Arvore AVL
		insereNoArvAVLPalavra(raiz, v[i]);
	}
}

// Funcao para buscar uma palavra na Arvore AVL
int buscaArvAVLPalavra(ArvAVL *raiz, char valor[]) {
	int flag = 0;
	struct NO2 *atual = *raiz;

	// Verifica se o no atual C) NULL
	if (atual != NULL) {
		// Se a palavra do no atual for igual a buscada, imprime as informacoes
		if (strcmp(atual->info.palavra, valor) == 0) {
			printf("Palavra encontrada: %s\nFrequencia: %d\n", atual->info.palavra, atual->info.frequencia);
			Filme *aux = atual->info.listaFilmes;
			// Exibe todas as citacoes relacionadas a palavra
			while (aux != NULL) {
				printf("\nCitacao: %s\n  Filme: %s\n  Ano: %s\n", aux->frase, aux->filme, aux->ano);
				aux = aux->prox;
			}
			flag = 1; // Palavra foi encontrada
		}

		// Chama recursivamente a busca na subArvore esquerda
		if (buscaArvAVLPalavra(&(atual->esq), valor)) {
			flag = 1;
		}
		// Chama recursivamente a busca na subArvore direita
		if (buscaArvAVLPalavra(&(atual->dir), valor)) {
			flag = 1;
		}
	}

	return flag; // Retorna 1 se encontrou a palavra, 0 caso contrC!rio
}


//leitura de arquivo
int arquivo(Palavra v[], char arq[]) {
	FILE *file = fopen(arq, "r");
	int pos=0;
	char linha[1000];
	char frase[1000];
	char filme[1000];
	char ano[1000];

	if(file==NULL) {
		printf("Erro ao abrir o arquivo!\n");
		return -1;
	}

	while(fgets(linha, 1000, file)) {

		linha[strcspn(linha, "\n")]='\0';

		if (sscanf(linha, "%[^;];%[^;];%[^;]", frase, filme, ano) == 3) {
			pos=criarVetorDePalavra(frase, filme, ano, v, pos);
		} else {
			printf("Linha invalida: %s\n", linha);
		}
	}
	fclose(file);
	return pos;
}



