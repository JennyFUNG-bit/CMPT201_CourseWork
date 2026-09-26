#define _GNU_SOURCE
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char *pathway = NULL;
  size_t len = 0;
  while (true) {
    printf("Enter programs to run.\n");
    if (getline(&pathway, &len, stdin) == -1)
      break;

    pid_t pid = fork();
    pathway[strcspn(pathway, "\n")] = '\0';
    if (pid < 0) {
      perror("fork");
      free(pathway);
    }
    if (pid == 0) {
      execlp(pathway, pathway, NULL);

      printf("Exec failure\n");
      perror("execlp");
      free(pathway);
      exit(EXIT_FAILURE);
    }

    if (waitpid(pid, NULL, 0)) {
      perror("waitpid");
    }
  }
  free(pathway);
  return 0;
}
