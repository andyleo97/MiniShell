#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void readLine(char line[64]);
void loop();
void createArgs(char *str, char **argVect);

int main() {

  loop();

  return 0;
}

void loop(){
  char str[64];
  char **args;

  while(1){
    printf("%s","mini-shell> ");
    readLine(str);
    createArgs(str, args);
    if (strcmp(args[0], "exit") == 0) {
      break;
    }
    printf("%s\n", str);
  }
}

void readLine(char line[64]){
  fgets(line, 64, stdin);
  strtok(line, "\n");
}

void createArgs(char *str, char **argVect){
  while(*str != "\0"){
    while (strcmp(*str, " ") == 0 || strcmp(*str,"\t") == 0 || strcmp(*str, "\n") == 0){
               *str++ = "\0";
    }
    while (strcmp(*str, '\0') != 0 && strcmp(*str, ' ') != 0 && strcmp(*str, '\t') != 0 && strcmp(*str, '\n') != 0) {
                   str++;
    }
  }
}
