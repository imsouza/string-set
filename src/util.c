#include "../headers/util.h"

#define ERROR(msg) fprintf(stderr, "[!]: %s\n", #msg)

void *
mallocSafe (size_t nbytes) {
  void *ptr = malloc (nbytes);
  
  if (ptr == NULL) {
    ERROR(erro ao alocar memória.);
    exit(EXIT_FAILURE);
  }

  return ptr;
}

  
void 
removerEspacos (char *str) {
  char *i = str;
  
  do {
    while (*i == ' ') {
      ++i;
    }
  } while ((*str++ = *i++));
}


void 
converterMinusculo (char *str) {
  for (int i = 0; i < strlen(str); i++) {
    str[i] = tolower(str[i]);
  }
}
