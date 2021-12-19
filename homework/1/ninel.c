// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#define INF 2000000000

int main() {
  int n, x, i;
  int penultimul, ultimul; // retin valorile ultimelor nr citite
  long long suma = 0;
  int contor = 0; // memoreaza numarul de copaci speciali
  double medie;
  int xmin_par = INF, xmax_impar = 0;
  penultimul = ultimul = 0;

  scanf("%d", &n);
  scanf("%d%d", &penultimul, &ultimul);
  // citim mai intai primele doua numere ca sa formam un triple
  // mai multe detalii se gasesc in fisierul README
  for (i = 0; i < n; i++) {
    scanf("%d", &x); // valoarea curenta citata

    if (penultimul < ultimul && ultimul > x) {
      // rezulta ca ultimul e copac special
      suma += ultimul;
      contor++;

      // daca suntem pe o pozitie para verificam daca e cel mai scund copac
      if ((i + 1) % 2 == 0 && ultimul < xmin_par)
        xmin_par = ultimul;

      // daca suntem pe o pozitie impara verificam daca e cel mai inalt copac
      else if ((i + 1) % 2 == 1 && ultimul > xmax_impar)
        xmax_impar = ultimul;
    }

    penultimul = ultimul;
    ultimul = x; // continuam formare de triplete
  }

  if (contor > 0)
    medie = (double) suma / contor;

  // tratam cazurile speciale
  if (xmin_par == INF) {
    if (contor == 0) {
      xmin_par = 0;
      xmax_impar = 0;
    } else {
      xmin_par = -1;
    }
  }
  printf("%lld\n%.7lf\n%d\n%d\n", suma, medie, xmax_impar, xmin_par);
  return 0;
}
