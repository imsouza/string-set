#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include "../headers/stringset.h"
#include "../headers/util.h"

int 
main (void) {
  system("clear");
  
  StringSet *raiz = TrieCriarNo();

  int opcoes;
  while(true){
    setbuf(stdin,NULL);
    printf("\n\n========= Árvore Digital Trie ==========");
    printf("\n=----------------OPÇÕES----------------=");
    printf(HGRN"\n[1] - Inserir"reset);
    printf(HYEL"\n[2] - Remover"reset);
    printf(HBLU"\n[3] - Buscar"reset);
    printf(HCYN"\n[4] - Buscar por prefixo"reset);
    printf(HWHT"\n[5] - Arvore vazia?"reset);
    printf(HWHT"\n[6] - Imprimir"reset);
    printf(HWHT"\n[7] - Testar todas as funções"reset);
    printf(HRED"\n[8] - Sair do programa\n"reset);
    printf("=--------------------------------------=\n");
    printf(HMAG"Digite a opção [1-8] -> "reset);
    scanf("%d", &opcoes);
    system("clear");
  
    switch(opcoes){
      case 1: {
        if (raiz == NULL){
          raiz = TrieCriarNo();
        }
        char palavra[WORDSIZE];
        printf("Informe a palavra a ser inserida: ");
        scanf("%s", palavra);
        TrieInserirPalavra(palavra, raiz);
        break;
      }

      case 2: {
        char palavra[WORDSIZE];
        printf("Informe a palavra a ser removida: ");
        scanf("%s", palavra);
        TrieRemoverPalavra(palavra, &raiz);
        break;
      }

      case 3: {
        char palavra[WORDSIZE];
        printf("Informe a palavra a ser buscada: ");
        scanf("%s", palavra);
        StringSet* busca;
        if ((busca = TrieBuscarPalavra(palavra, raiz))){
          printf("\n\"%s\" foi encontrada", palavra);
        }
        else{
          printf(HRED"\n[!] \"%s\" não foi encontrada"reset, palavra);
        }
        break;
      }

      case 4: {
        char palavra[WORDSIZE];
        printf("Informe o prefixo: ");
        scanf("%s", palavra);
        TrieExibirPrefixos(palavra, raiz);
        break;
      }

      case 5:
        if (TrieEstaVazia(raiz)){
          printf(HRED"\n[!] A árvore está vazia."reset);
        }
        else{
          printf(HGRN"\nA árvore não está vazia."reset);
        }
        break;
      
      case 6:
        TrieExibirArvore(raiz);
        printf("Tamannho: %d", TrieTamanho(raiz));
        break;
    
      case 7: {
          TrieLiberarMemoria(raiz);
          raiz = TrieCriarNo();
          char palavras[][WORDSIZE] = {
          "abacate",
          "abacates",
          "abacaxi",
          "amazonia",
          "aba",
          "abba",
          "atlas",
          "zebra",
          "abatido",
          "melancia",
          "universidade",
          "unicornio",
          "zooboomafu",
          "pacote",
          "trigo",
          "gelo",
          "gelado",
          "triplo",
          "ferrari",
        };
  
        for (int i = 0; i < sizeof(palavras) / WORDSIZE; i++) {
          TrieInserirPalavra(palavras[i], raiz);
        }

        TrieExibirArvore(raiz);
        printf("Tamanho: %i\n",  TrieTamanho(raiz));
  
        TrieExibirPrefixos("uni", raiz);
        TrieExibirPrefixos("aba", raiz);
        TrieExibirPrefixos("gel", raiz);
        TrieExibirPrefixos("mec", raiz);
  
        TrieRemoverPalavra(palavras[10], &raiz);
        TrieExibirArvore(raiz);
        printf("Tamanho: %i\n",  TrieTamanho(raiz));
  
        TrieRemoverPalavra(palavras[11], &raiz);
        TrieExibirArvore(raiz);
        printf("Tamanho: %i\n",  TrieTamanho(raiz));

        TrieExibirPrefixos("uni", raiz);

        TrieInserirPalavra(palavras[11], raiz);
        TrieExibirArvore(raiz);
        printf("Tamanho: %i\n",  TrieTamanho(raiz));

        TrieInserirPalavra(palavras[11], raiz);
        TrieExibirArvore(raiz);
        printf("Tamanho: %i\n",  TrieTamanho(raiz));

        printf("\nBuscando palavra \"%s\"\n", palavras[18]);
        StringSet *busca = TrieBuscarPalavra(palavras[18], raiz);
        busca ? printf("Achou! {\"%s\"}\n", palavras[18]) :  \
              printf("Palavra não encontrada. {\"%s\"}\n", palavras[18]);

        char p[] = "caminhao";
        printf("\nBuscando palavra \"%s\"\n", p);
        busca = TrieBuscarPalavra(p, raiz);
        busca ? printf("Achou! {\"%s\"}\n", p) :  \
                printf("Palavra não encontrada. {\"%s\"}\n", p);

        for (int i = 0; i < sizeof(palavras) / WORDSIZE; i++) {
          TrieRemoverPalavra(palavras[i], &raiz);
        }

        TrieExibirArvore(raiz);
        printf("Tamanho: %i\n",  TrieTamanho(raiz));
        TrieLiberarMemoria(raiz);
        exit(EXIT_SUCCESS);
      }

      case 8:
        TrieLiberarMemoria(raiz);
        exit(EXIT_SUCCESS);
    
      default:
        continue;
    }
  }
  
  TrieLiberarMemoria(raiz);

  return 0;
}