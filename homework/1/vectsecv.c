// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#define LMAX 100

void construieste(int n, int numere[2]) {
  int frecv[10] = {0}, i, j;
  do {
    frecv[n % 10]++;
    n /= 10;
  } while (n > 0);
  numere[0] = 0;
  for (i = 0; i <= 9; i++)
    for (j = 1; j <= frecv[i]; j++)
      numere[0] = numere[0] * 10 + i;
  numere[1] = 0;
  for (i = 9; i >= 0; i--)
    for (j = 1; j <= frecv[i]; j++)
      numere[1] = numere[1] * 10 + i;
}

// returneaza pozitia unui element in vector
// sau -1 daca elementul nu se afla in vector
int cauta(int cheie, int v[LMAX], int nr) {
  int i;
  for (i = 0; i < nr; i++)
    if (cheie == v[i])
      return i;
  return -1;
}

int main() {
  int n, x, i;
  int v[LMAX] = {0}, nr = 0;
  int numere[2];
  // pe pozitia 0 din numere[] retinem numarul format din sortarea crescatoare
  // a cifrelor unui numar, iar pe pozitia 1, numarul format din sortarea
  // descrescatoare

  scanf("%d", &n);
  construieste(n, numere);

  // calculam diferenta
  x = numere[1] - numere[0];
  while (cauta(x, v, nr) == -1) { // daca nu a mai aparut pana acum
    v[nr++] = x; // o inseram in lista
    construieste(x, numere); // continuam procesul de constructie
    x = numere[1] - numere[0]; // si din noul calculam diferenta
  }
  // diferenta care se repeta a ramas stocata in variabila x si nu a fost
  // inserata in vector, deci cautam pozitia primei sale aparitii in vector
  i = cauta(x, v, nr);
  printf("%d\n", i);
  // si afisam numerele de pana in perioada
  while (i < nr) {
    printf("%d ", v[i]);
    i++;
  }
  return 0;
}
