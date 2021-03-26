#include"strutil.h"
#include<string.h>
#include<stdlib.h>

#define TAM_STR_V 1000

char *strdup(const char *s);

size_t calcular_tam(const char* str, char sep) {
  size_t cant_sep = 0;
  for(size_t i = 0; i < strlen(str); i++) {
    if(str[i] == sep) cant_sep++;
  }
  return cant_sep + 2;
}

char** split(const char* str, char sep) {
  if(sep == '\0') return NULL;
  size_t tam = calcular_tam(str, sep);
  char** strv = malloc(sizeof(char*)*tam);
  if(!strv) return NULL;

  size_t pos_string = 0, pos_strv = 0;
  char string[TAM_STR_V];
  size_t largo_str = strlen(str);
  for(int i = 0; i <= largo_str; i++) {
    if(str[i] == sep || str[i] == '\0') {
      string[pos_string] = '\0';
      pos_string = 0;
      strv[pos_strv] = strdup(string);
      if(!strv[pos_strv]) {
        free_strv(strv);
        return NULL;
      }
      pos_strv++;
    }
    else {
      string[pos_string] = str[i];
      pos_string++;
    }
  }
  strv[pos_strv] = NULL;
  return strv;
}

void free_strv(char* strv[]) {
  int i = 0;
  while(strv[i]) {
    free(strv[i]);
    i++;
  }
  free(strv);
}
