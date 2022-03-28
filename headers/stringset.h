#ifndef _STRINGSET_H_
#define _STRINGSET_H_

#include "util.h"

typedef struct stringset StringSet;
typedef char String;

StringSet *TrieCriarNo();
StringSet *TrieBuscarPalavra(String *, StringSet *);
void TrieInserirPalavra(String *, StringSet *);
void TrieExibirArvore(StringSet *);
void TrieExibirPrefixos(String *, StringSet *);
void TrieRemoverPalavra(String *, StringSet **);
int TrieTamanho(StringSet *);
void TrieLiberarMemoria(StringSet *);
bool TrieEstaVazia(StringSet*);

#endif