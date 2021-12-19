// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#include <stdio.h>
#include <stdlib.h>
#define NMAX 100

void sort(int v[NMAX], int st, int dr) {
  // sortam prin interschimbare
  int i, j, aux;
  for (i = st; i <= dr - 1; i++)
    for (j = i + 1; j <= dr; j++)
      if (v[i] > v[j]) {
        aux = v[i];
        v[i] = v[j];
        v[j] = aux;
      }
}

int main() {
  int n, i, credit;
  int nota[NMAX], diferenta[NMAX], punctaj, p_min;
  // detalii asupra acestei implementari se gasesc in fisierul README
  scanf("%d", &n);
  punctaj = 0;
  for (i = 0; i < n; i++)
    scanf("%d", &nota[i]);
  for (i = 0; i < n; i++) {
    scanf("%d", &credit);
    diferenta[i] = (10 - nota[i]) * credit;
    punctaj += nota[i] * credit;
  }
  // sortam crescator
  sort(diferenta, 0, n - 1);
  // parcurgem diferentele in ordine inversa de la cea mai mare
  // la cea mai mica
  scanf("%d", &p_min);
  i = n - 1;
  while (punctaj < p_min && i >= 0) {
    punctaj += diferenta[i];
    i--;
  }
  // afisam numarul de materii la care se duce Mihai la marire
  if (punctaj >= p_min)
    printf("%d\n", n - 1 - i); // numarul de materii adunate
  else
    printf("-1\n");
  return 0;
}
