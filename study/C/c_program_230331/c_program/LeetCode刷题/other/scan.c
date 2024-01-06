#include <stdio.h>
#include <string.h>

char* reverseWords(char* str) {

  char* copy = strdup(str);

  char* tokens[100];
  int count = 0;
  char* token = strtok(copy, " ");

  while(token != NULL) {
  tokens[count++] = token;
  token = strtok(NULL, " ");
  }

  tokens[count] = NULL;

  char* result = malloc(strlen(str)+1); 
  int i;

  for(i=count-1; i>=0; i--) {
  strcat(result, tokens[i]);
  if(i!=0)
    strcat(result, " ");
  }

  free(copy);

  return result;
}

int main() {

  char* string = "hello world";
  char* reversed = reverseWords(string);

  printf("%s\n", reversed);

  free(reversed);

  return 0;
}
