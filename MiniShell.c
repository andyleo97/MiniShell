#define _GNU_SOURCE
#include <pwd.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void readLine(char *line);
void loop();
void createArgs(char *str, char **argVect);
void execute(char **args);
int myClone(void *);
int mapCloneArgs(char **args);

int main() {

  loop();

  return 0;
}

void loop() {
  char *str = malloc(sizeof(char *) * 1024);
  char **args = malloc(sizeof(char **) * 1024);
  void **child_stack;

  while (1) {
    printf("%s", "mini-shell> ");
    readLine(str);
    createArgs(str, args);

    if (strcmp(args[0], "exit") == 0) {
      free(str);
      free(args);
      break;
    }
    else if (strcmp(args[0], "clone") == 0) {
      int cloneArg = mapCloneArgs(args);

      if (cloneArg == 0) {
        continue;
      }
      int stat;
      child_stack = malloc(16384);
      pid_t retId =
          clone(myClone, child_stack, mapCloneArgs(args) | SIGCHLD, NULL);
      pid_t id = waitpid(retId, &stat, 0);
      continue;
    }
    else if (strcmp(args[0], "cd") == 0) {
      char *newDir = args[1];
      if (args[1] == NULL || strcmp(args[1], "~") == 0) {
        newDir = getenv("HOME");
      }
      int error = chdir(newDir);
      if (error != 0) {
        printf("Change Directory Failed\n");
      }
    } else {
      execute(args);
    }
  }
}

void readLine(char *line) {
  fgets(line, 64, stdin);
  strtok(line, "\n");
}

void createArgs(char *str, char **argVect) {
  while (*str != '\0') {
    while (*str == ' ' || *str == '\t' || *str == '\n') {
      *str++ = '\0';
    }
    *argVect++ = str;
    while (*str != '\0' && *str != ' ' && *str != '\t' && *str != '\n') {
      str++;
    }
    *argVect = '\0';
  }
}

void execute(char **args) {
  pid_t id;
  int stat;

  if ((id = fork()) < 0) {
    printf("%s\n", "Fork failed");
    ;
    exit(1);
  }
  else if (id == 0) {
    if (execvp(*args, args) < 0) {
      printf("%s\n", "command not found: try again");
      exit(1);
    }
  }
  else {
    while (wait(&stat) != id)
      ;
  }
}

int myClone(void *args) {
  loop();
  return 0;
}

int mapCloneArgs(char **args) {
  if (args[1] != NULL) {

    if (strcmp(args[1], "ns") == 0) {
      return 0x00020000;
    }
    if (strcmp(args[1], "ipc") == 0) {
      return 0x08000000;
    }
    if (strcmp(args[1], "user") == 0) {
      return 0x10000000;
    }
    if (strcmp(args[1], "net") == 0) {
      return 0x40000000;
    }
    if (strcmp(args[1], "uts") == 0) {
      return 0x04000000;
    }
  }
  printf("Usage: clone ns | net | ipc | user | uts\n");
  return 0;
}
