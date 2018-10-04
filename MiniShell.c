#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void readLine(char *line);
void loop();
void createArgs(char *str, char **argVect);

int main() {

  loop();

  return 0;
}

void loop(){
  char *str = malloc(sizeof(char*) * 64);
  char **args = malloc(sizeof(char**) * 64);

  while(1){
    printf("%s","mini-shell> ");
    readLine(str);
    createArgs(str, args);
    if (strcmp(args[0], "exit") == 0) {
      break;
    }
  }

}

void readLine(char *line){
  fgets(line, 64, stdin);
  strtok(line, "\n");
}

void createArgs(char *str, char **argVect){
  while(*str != '\0'){
    while (*str == ' '|| *str == '\t' || *str ==  '\n'){
               *str++ = '\0';
    }
    *argVect++ = str;
    while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n') {
                   str++;
    }
    *argVect = '\0';
  }

}

/*
int i = 0;
while(i<10){
  printf("%c\n", *str);
  //*str++;
  i++;
}



*/
