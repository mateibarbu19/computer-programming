// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#include <commands.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char comenzi[RECORDSIZE + 1];
  int ok = 1;

  while (ok && fgets(comenzi, RECORDSIZE + 1, stdin) != NULL) {
    comenzi[strlen(comenzi) - 1] = '\0';

    if (strstr(comenzi, "create ") == comenzi) {
      if (parameter_count(comenzi) != 2)
        printf("> Wrong command!\n");
      else
        create(comenzi);
    } else if (strstr(comenzi, "list ") == comenzi) {
      if (parameter_count(comenzi) != 1)
        printf("> Wrong command!\n");
      else
        list(comenzi);
    } else if (strstr(comenzi, "extract ") == comenzi) {
      if (parameter_count(comenzi) != 2)
        printf("> Wrong command!\n");
      else
        extract(comenzi);
    } else if (strcmp(comenzi, "exit") == 0) {
      ok = 0;
    } else {
      printf("> Wrong command!\n");
    }
  }
  return 0;
}
