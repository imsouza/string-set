#include "../headers/stringset.h"
#include "../headers/util.h"

struct stringset {
  bool fimPalavra;
  StringSet *pai;
  StringSet *filhos[ALSIZE];
};


StringSet *
TrieCriarNo () {
  StringSet *trie = mallocSafe (sizeof(StringSet));
  
  trie->fimPalavra = false;
  trie->pai = NULL;
  
  for (int i = 0; i < ALSIZE; i++) {
    trie->filhos[i] = NULL;
  }

  return trie;
}


StringSet *
TrieBuscarPalavra (String *palavra, StringSet *trie) {
  if (TrieEstaVazia(trie)) return NULL;
  for (int i = 0; i < strlen(palavra); i++) {
    int index = palavra[i] - 97;

    if (trie->filhos[index]) {
      trie = trie->filhos[index];
    } else {
      return NULL;
    }    
  }

  if (trie->fimPalavra) {
    return trie;
  } else {
    return NULL;
  }
}


StringSet *
TrieBuscarPrefixo (String *palavra, StringSet *trie) { 
  if (TrieEstaVazia(trie)) return NULL;
  for (int i = 0; i < strlen(palavra); i++) {
    int index = palavra[i] - 97;

    if (trie->filhos[index]) {
      trie = trie->filhos[index];
    } else {
      return NULL;
    }    
  }

  return trie;
}


void 
TrieInserirPalavra (String *palavra, StringSet *trie) {
  StringSet *busca;
  int index;

  converterMinusculo(palavra);
  removerEspacos(palavra);

  if (!(busca = TrieBuscarPalavra(palavra, trie))) {
    printf(HGRN"\nINSERINDO {"HWHT"\"%s\""reset""HGRN"}\n"reset, palavra);
    for (int i = 0; i < strlen(palavra); i++) {
      index = palavra[i] - 97;
  
      if (trie->filhos[index] == NULL) {
        StringSet *temp = TrieCriarNo();
        trie->filhos[index] = temp;
        temp->pai = trie;
      }
  
      trie = trie->filhos[index];
    }
    
    trie->fimPalavra = true;
  } else {
    printf(HRED"\n[!] String duplicada. [%s]\n"reset, palavra);
    return;
  }
}


void 
TrieRemoverPalavra (String *palavra, StringSet **trie) {
  StringSet *no;
  
  if ((no = TrieBuscarPalavra(palavra, *trie))) {
    printf(HYEL"\nREMOVENDO {"HWHT"\"%s\""reset""HYEL"}\n"reset, palavra);
    int filhosNull;
    for (filhosNull = 0; filhosNull < ALSIZE; filhosNull++){
      if (no->filhos[filhosNull] != NULL) break;
    }

    if (filhosNull == ALSIZE){
      while(true){
        StringSet *temp = no;
        no = temp->pai;

        if (no == NULL) {
          free(temp);
          *trie = NULL;
          break;
        }
        
        int qntIrmaos = 0;
        for (int i = 0; i < ALSIZE; i++){
          if (no->filhos[i] != NULL){
            qntIrmaos++;
            if (no->filhos[i] == temp){
               no->filhos[i] = NULL;
            }
          } 
        }      
        
        free(temp);
        
        if (no->fimPalavra) break;
        else if (qntIrmaos > 1) break;
      }
    }
    else {
      no->fimPalavra = false;
    }
  }
  else {
    printf(HRED"\n[!] Palavra não encontrada. [%s]\n"reset, palavra);
  }
}


void
TrieRealizarPercurso (String *palavra, int index, StringSet *trie) {
  if (trie == NULL) { return; }
  
  if (trie->fimPalavra) {
    for (int i = 0; i < index; i++) {
      if (i == index - 1) {
        printf(HGRN"%c"reset, palavra[i]); 
        break;
      }

      if (strcmp(&palavra[i], " ") > 0) {
        printf("%c", palavra[i]);
      }  
    }
  
    putchar('\n');
  }

  for (int i = 0; i < ALSIZE; i++) {
    if (trie->filhos[i] != NULL) {
      palavra[index] = i + 97;
      TrieRealizarPercurso(palavra, index + 1, trie->filhos[i]);
    }
  } 
}


void
TrieRealizarPercursoPrefixo (String *prefixo, String *resto, int index, StringSet *trie) {
  if (trie == NULL) { return; }
  
  if (trie->fimPalavra) {
    printf(HCYN"%s"reset, prefixo);
    for (int i = 0; i < index; i++) {
      if (strcmp(&resto[i], " ") > 0) {
        printf("%c", resto[i]);
      }  
    }

    putchar('\n');
  }

  for (int i = 0; i < ALSIZE; i++) {
    if (trie->filhos[i] != NULL) {
      resto[index] = i + 97;
      TrieRealizarPercursoPrefixo(prefixo, resto, index + 1, trie->filhos[i]);
    }
  } 
} 


void
TrieExibirArvore (StringSet *trie) {
  if (!TrieEstaVazia(trie)){
    char *buffer = calloc (BUFFSIZE, sizeof(char));

  printf(HMAG"\nÁRVORE [\n"reset);
  TrieRealizarPercurso(buffer, 0, trie);
  printf(HMAG"]\n"reset);

  free(buffer);
  }
  else{
    printf(HMAG"\nÁRVORE [\n"reset);
    printf(HRED"[!] Árvore vazia.\n"reset);
    printf(HMAG"]\n"reset);
  } 
}


void 
TrieExibirPrefixos (String *prefixo, StringSet *trie) {
  StringSet *busca;
  if ((busca = TrieBuscarPrefixo(prefixo, trie))) {    
    char *buffer = calloc (BUFFSIZE, sizeof(char));
    printf(HMAG"\nPREFIXO {"HBLU"\"%s\""reset""HMAG"} [\n"reset, prefixo);
    TrieRealizarPercursoPrefixo(prefixo, buffer, 0, busca);
    printf(HMAG"]\n"reset);
    free(buffer);
 } else {
    printf(HRED"\n[!] Prefixo não encontrado: \"%s\"\n"reset, prefixo);
  }
}


void
TrieCalcularTamanho (int *size, StringSet *trie) {
  if (trie->fimPalavra) {
    *size = *size + 1;
  }

  for (int i = 0; i < ALSIZE; i++){
    if (trie->filhos[i]) {
      TrieCalcularTamanho(size, trie->filhos[i]);
    }
  }
}


int
TrieTamanho (StringSet *trie) {
  if (TrieEstaVazia(trie)){
    printf(HRED"\n[!] Árvore vazia.\n"reset);
    return 0;
  }
  int size = 0;
  TrieCalcularTamanho(&size, trie);
  return size;
}


bool
TrieEstaVazia (StringSet *trie) {
  if (trie){
    for (int i = 0; i < ALSIZE; i++){
      if (trie->filhos[i] != NULL) return false;
    }
  }
  return true;
}


void
TrieLiberarMemoria (StringSet *trie) {
  if (trie != NULL) {
    for (int i = 0; i < ALSIZE; i++) {
      if (trie->filhos[i] != NULL) {
        TrieLiberarMemoria(trie->filhos[i]);
      }
    }
  
    if (trie != NULL) {
      free(trie);
      trie = NULL; 
    }
  }
}