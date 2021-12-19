// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NMAX 100
#define KMAX 1 + NMAX / 2
// putem avea maxim jumatate din NMAX plus 1 de grupari pe linie/coloana

int ok_lin(int mat[NMAX][NMAX], int n, int m, int lin[NMAX][1 + NMAX / 2]) {
  int i, j, in_secv, poz, nr_caract;
  int ok = 1;
  for (i = 0; i < n && ok; i++) {
    in_secv = 0;   // memoreaza daca suntem intr-o grupare, 0 daca nu, altfel 1
    poz = 0;       // memoreaza in ce grupare suntem
    nr_caract = 0; // numarul de caractere la care am ajuns in grupare
    for (j = 0; j < m && ok; j++) {
      if (mat[i][j] == 1) {
        if (in_secv == 0) {
          in_secv = 1; // intram intr-o noua grupare
          poz++; // ne mutam in alta grupare
          nr_caract = 1;
          if (poz > lin[i][0]) { // daca depasim nr de grupari de pe o linie
            ok = 0;
          }
        } else if (in_secv == 1) {
          nr_caract++;
        }
      } else if (mat[i][j] == 0) {
        if (in_secv == 1) {
          in_secv = 0; // iesim dintr-o secventa

          // daca in secventa de pana acum
          // numarul de caractere nu este egal cu cel al gruparii corespondente
          if (nr_caract != lin[i][poz])
            ok = 0;
        }
      }
    }
    if (in_secv == 1) {
      if (nr_caract != lin[i][poz])
        ok = 0;
    }
    if (poz < lin[i][0])
      ok = 0;
  }
  return ok;
}

int ok_col(int mat[NMAX][NMAX], int n, int m, int col[NMAX][1 + NMAX / 2]) {
  // explicatiile sunt exact aceleasi ca si la functia anterioara
  int i, j, in_secv, poz, nr_caract;
  int ok = 1;
  for (j = 0; j < m && ok; j++) {
    in_secv = 0;   // daca suntem intr-o grupare
    poz = 0;       // memoreaza in ce grupare suntem
    nr_caract = 0; // numarul de caractere la care am ajuns in grupare
    for (i = 0; i < n && ok; i++) {
      if (mat[i][j] == 1) {
        if (in_secv == 0) {
          in_secv = 1;
          poz++; // ne mutam in alta grupare
          nr_caract = 1;
          if (poz > col[j][0]) {
            ok = 0;
          }
        } else if (in_secv == 1) {
          nr_caract++;
        }
      } else if (mat[i][j] == 0) {
        if (in_secv == 1) {
          in_secv = 0;
          if (nr_caract != col[j][poz])
            ok = 0;
        }
      }
    }
    if (in_secv == 1)
      if (nr_caract != col[j][poz])
        ok = 0;
    if (poz < col[j][0])
      ok = 0;
  }
  return ok;
}

int main() {
  int mat[NMAX][NMAX];
  int lin[NMAX][KMAX];
  int col[NMAX][KMAX];
  int t, n, m, i, j, ok;
  scanf("%d", &t);

  ok = 1;
  while (t > 0) {
    // citim mai intai datele de intrare
    scanf("%d%d", &n, &m);

    for (i = 0; i < n; i++) {
      scanf("%d", &lin[i][0]);
      for (j = 1; j <= lin[i][0]; j++)
        scanf("%d", &lin[i][j]);
    }
    for (i = 0; i < m; i++) {
      scanf("%d", &col[i][0]);
      for (j = 1; j <= col[i][0]; j++)
        scanf("%d", &col[i][j]);
    }
    for (i = 0; i < n; i++)
      for (j = 0; j < m; j++)
        scanf("%d", &mat[i][j]);

    ok = ok_lin(mat, n, m, lin); // verificam daca nomograma e corecta pe linii
    ok = ok & ok_col(mat, n, m, col); // si daca e corecta pe coloane

    if (ok == 1)
      printf("Corect\n");
    else
      printf("Eroare\n");

    t--;
  }
  return 0;
}
