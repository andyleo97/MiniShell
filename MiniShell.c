#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include  <sys/types.h>
#include  <sys/wait.h>
#include "unistd.h"

void readLine(char *line);
void loop();
void createArgs(char *str, char **argVect);
void execute(char **args);


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
    execute(args);
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

void execute(char **args){
    pid_t pid;
    int status;

    if ((pid = fork()) < 0) {
          printf("%s\n", "Fork failed");;
          exit(1);
     }
     else if (pid == 0) {
          if (execvp(*args, args) < 0) {
               printf("%s\n", "command not found: try again");
               exit(1);
          }
     }
     else {
          while (wait(&status) != pid)
          ;
     }
}
