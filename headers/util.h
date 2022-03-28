#ifndef UTIL_H_
#define UTIL_H_

#define HBLK "\e[0;90m"
#define HRED "\e[0;91m"
#define HGRN "\e[0;92m"
#define HYEL "\e[0;93m"
#define HBLU "\e[0;94m"
#define HMAG "\e[0;95m"
#define HCYN "\e[0;96m"
#define HWHT "\e[0;97m"
#define reset "\e[0m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>

#define ALSIZE 27
#define WORDSIZE 50
#define BUFFSIZE 10000

typedef enum {
  false,
  true
} bool;

void *mallocSafe(size_t);
void removerEspacos(char *);
void converterMinusculo(char *);

#endif