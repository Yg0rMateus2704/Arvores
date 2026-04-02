#include "busca.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {

  int opcao;
  int auxArq;
  int tam;

  do {
    Palavra v[1000] = {0};

    printf("Escolha um arquivo\n");
    printf("1- Arquivo um\n");
    printf("2- Arquivo dois\n");
    printf("3- Arquivo tres\n");
    printf("4- Sair\n");

    scanf("%d", &auxArq);

    switch (auxArq) {
    case 1:
      tam = arquivo(v, "um.txt");
      break;
    case 2:
      tam = arquivo(v, "dois.txt");
      break;
    case 3:
      tam = arquivo(v, "tres.txt");
      break;
    case 4:
      printf("Obrigado por utilizar os nossos servicos. Ate logo!");
      return 0;
    default:
      printf("Desculpe, nao consegui ententer. Digite uma opcao valida.\n");
      continue;
    }
    do {
      printf("\nEscolha uma opcao");
      printf("\n1- Pesquisa Binaria");
      printf("\n2- Arvore Binaria de Busca");
      printf("\n3- Arvore AVL");
      printf("\n4- Voltar ao menu anterior\n");

      scanf("%d", &opcao);

      switch (opcao) {
      case 1: {
        time_t ini;
        time_t fim;
        double tempoTotal;
        char chave[50];
        printf("Digite a palavra que deseja procurar: ");
        scanf("%s", chave);
        InsertionSort(v, tam);
        ini = clock();
        BuscaBinaria(v, chave, 0, tam - 1);
        fim = clock();
        tempoTotal = (double)(fim - ini) / CLOCKS_PER_SEC;
        printf("O tempo total necessario para a Busca Binaria foi de %lf "
               "segundos\n",
               tempoTotal);
        break;
      } case 2: {
        time_t ini;
        time_t fim;
        double tempoTotal;
        char chave[50];
        int flag;
        ArvBin *raiz = criaArvoreBinaria();
        insercaoArvBin(raiz, v, tam);
        printf("Digite a palavra que deseja procurar: ");
        scanf("%s", chave);
        ini = clock();
        flag = buscaArvoreBinaria(raiz, chave);
        fim = clock();
        tempoTotal = (double)(fim - ini) / CLOCKS_PER_SEC;
        printf("O tempo total necessario para a Arvore Binaria de Busca foi de "
               "%lf segundos\n",
               tempoTotal);
        break;

      } case 3: {
        int n;
        int flag;
        time_t ini;
        time_t fim;
        double tempoTotal;

        do {
          printf("Deseja realizar a busca por:\n   1- Palavra\n   2- "
                 "Frequencia\n");
          scanf("%d", &n);

          if (n == 1) {
            flag = 0;
            ArvAVL *avl1 = cria_ArvAVL();
            InsercaoArvAVLPalavra(v, avl1, tam);
            char str[20];
            printf("Digite a palavra que deseka buscar: ");
            scanf("%s", str);
            ini = clock();
            flag = buscaArvAVLPalavra(avl1, str);
            fim = clock();
            tempoTotal = (double)(fim - ini) / CLOCKS_PER_SEC;
            if (flag == 0)
              printf("Palavra nao encontrada!\n");
            printf("O tempo total necessario de busca na Arvore AVL foi de %lf "
                   "segundos\n",
                   tempoTotal);
            break;

          } else if (n == 2) {
            flag = 0;
            int f;
            ArvAVL *avl2 = cria_ArvAVL();
            InsercaoArvAVLFreq(v, avl2, tam);
            printf("Digite a frequencia que deseja procurar: ");
            scanf("%d", &f);
            ini = clock();
            flag = buscaArvAVL(avl2, f);
            fim = clock();
            tempoTotal = (double)(fim - ini) / CLOCKS_PER_SEC;
            if (flag == 0)
              printf("Frequencia nao encontrada!\n");
            printf("O tempo total necessario de busca na Arvore AVL foi de %lf "
                   "segundos\n",
                   tempoTotal);
            break;
          } else {
            printf("Desculpe, nao consegui entender. Digite uma opcao valida, "
                   "por favor.\n");
          }
        } while (n != 1 && n != 2);
        break;
      }
      case 4:
        break;
      default:
        printf("Desculpe, nao consegui entender. Digite uma opcao valida, por "
               "favor.\n");
        break;
      }
    } while (opcao != 4);

  } while (auxArq != 4);

  return 0;
}
