// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)
#include <stdio.h>
#include <stdlib.h>

void free_matrix(int **mat, int n) {
  int i;
  for (i = 0; i < n; i++) {
    free(mat[i]);
  }
  free(mat);
}

void alloc_matrix_line(int **mat, int i, int m) {
  mat[i] = calloc(m, sizeof(int));
  if (mat[i] == NULL) {
    free_matrix(mat, i - 1);
    exit(1);
  }
}

int **alloc_matrix(int n) {
  int **mat;
  mat = calloc(n, sizeof(int *));
  if (mat == NULL)
    exit(-1);
  return mat;
}

size_t end(int *linie) {
  // returneaza numarul de octeti pe care il ocupa linia
  // adica care e pozitia de dupa ultimul octet, sfarsitul
  return sizeof(int) + linie[0] * sizeof(int);
}

void resize_line(int **mat, int linie, size_t nouadim) {
  // functia acesta redimensioneaza o linie din matrice
  size_t i;
  char *p;
  mat[linie] = realloc(mat[linie], nouadim);
  p = (char *)mat[linie];
  for (i = end(mat[linie]); i < nouadim; i++)
    p[i] = 0;
  // am completat cu 0 pe valorile de pe noile pozitii alocate
  mat[linie][0] = nouadim / sizeof(int) - 1;
  // am actualizat numarul de elemente de pe linie
}

int **read_map(int n) {
  // acesta este functia pentru citirea matricii
  int **mat = alloc_matrix(n);
  int i, j, m;
  for (i = 0; i < n; i++) {
    scanf("%d", &m);
    alloc_matrix_line(mat, i, m + 1);
    // am indexat de la 1
    mat[i][0] = m;
    // si stocam pe prima pozitie de pe linie numarul de elemente
    // intrucat matricea nu este dreptunghiulara
    for (j = 1; j <= m; j++)
      scanf("%X", &mat[i][j]);
  }
  return mat;
}

double medie_gard(int **mat, int n) {
  // pentru mai multe detalii despre acesta functie citi fisierul README
  char *p;
  int i, suma = 0, contor = 0;
  size_t j;

  for (i = 0; i < n; i += n - 1) {
    p = (char *)mat[i];
    for (j = sizeof(int); j < end(mat[i]); j++) {
      suma += p[j];
      contor++;
    }
  }
  for (i = 1; i < n - 1; i++) {
    p = (char *)mat[i];
    suma += p[sizeof(int)] + p[end(mat[i]) - 1];
    contor += 2; // adunam doar primul si ultimul element de pe linie
  }

  return (double)suma / contor;
}

size_t dimensiune(char tip) {
  // intoarce numarul de octeti ai tipului de date corespunzator codificarilor
  if (tip == 'C')
    return sizeof(char);
  if (tip == 'S')
    return sizeof(short);
  if (tip == 'I')
    return sizeof(int);
  return 0;
}

void modify(int *vector, size_t dim, int indexdate, int valnoua) {
  // intrucat am indexat de la 1 elementele era mai usor sa sarim peste
  // prima pozitie de pe linie, unde era stocat numarul de elemente
  char *p = (char *)(vector + 1);
  char *val = (char *)&valnoua;
  size_t j;
  // urmeaza sa copiam octet cu octet noua valoare
  for (j = 0; j < dim; j++)
    p[(indexdate - 1) * dim + j] = val[j];
}

void swap(int *vector, size_t dim, int indexdate) {
  // intrucat am indexat de la 1 elementele era mai usor sa sarim peste
  // prima pozitie de pe linie, unde era stocat numarul de elemente
  char *p = (char *)(vector + 1), aux;
  size_t i;
  // urmeaza sa interschimbam octet cu octet din element
  for (i = 0; i < dim / 2; i++) {
    aux = p[indexdate * dim + i];
    p[indexdate * dim + i] = p[indexdate * dim + dim - i - 1];
    p[indexdate * dim + dim - i - 1] = aux;
  }
}

int fill(char **p, int n, int i, size_t ji) {
  int contor = 1;
  p[i][ji] = 1; // am vizitat acesta casuta si nu vrem sa o mai vizitam
  // deci mazgalim pe harta o valoare ca sa stim ca am luat in calcul
  // acesta gaura neagra
  // verifcam mereu daca pe linia pe care urmează să ne deplasăm
  // avem memorie alocată pe coloana respectivă
  // si daca pe acea coloana este o gaura neagra

  if (i > 0 && ji < end((int *)p[i - 1]) && !p[i - 1][ji])
    contor += fill(p, n, i - 1, ji); // ne deplasam in jos

  if (i + 1 < n && ji < end((int *)p[i + 1]) && !p[i + 1][ji])
    contor += fill(p, n, i + 1, ji); // ne deplasam in sus

  if (ji > sizeof(int) && ji < end((int *)p[i]) && !p[i][ji - 1])
    contor += fill(p, n, i, ji - 1); // // ne deplasam la stanga

  if (ji + 1 < end((int *)p[i]) && !p[i][ji + 1])
    contor += fill(p, n, i, ji + 1); // ne deplasam la dreapta

  return contor;
}

int main() {
  int **mat, n, k, i, j;
  int linie, indexdate, valnoua, masa, masa_max, coord_lin, coord_col;
  char **p, operatie, tip;
  size_t nouadim, ji;

  scanf("%d", &n);
  mat = read_map(n);

  printf("task 1\n");
  printf("%.8lf\n", medie_gard(mat, n));

  printf("task 2\n");
  scanf("%d", &k);
  for (; k > 0; k--) {
    scanf(" %c %c%d%d", &operatie, &tip, &linie, &indexdate);
    if (operatie == 'M') {
      if (end(mat[linie]) < indexdate * dimensiune(tip) + sizeof(int)) {
        // daca nu avem suficient spatiu pe linie redimensionam linia
        nouadim = indexdate * dimensiune(tip) + sizeof(int);
        if (nouadim % sizeof(int) > 0)
          nouadim += sizeof(int) - nouadim % sizeof(int);
        // realocam un multiplu de sizeof(int) elemente pe linie
        resize_line(mat, linie, nouadim);
      }
      scanf("%X", &valnoua);
      modify(mat[linie], dimensiune(tip), indexdate, valnoua);
    }
    if (operatie == 'D')
      modify(mat[linie], dimensiune(tip), indexdate, 0);
    if (operatie == 'S')
      swap(mat[linie], dimensiune(tip), indexdate);
  }
  for (i = 0; i < n; i++) {
    for (j = 1; j <= mat[i][0]; j++)
      printf("%08X ", mat[i][j]);
    printf("\n");
  }

  printf("task 3\n");
  masa_max = 0;
  p = (char **)mat;
  for (i = 0; i < n; i++)
    for (ji = sizeof(int); ji < end(mat[i]); ji++)
      if (p[i][ji] == 0) {
        // daca la acea pozitie este o gaura neagra, calculam masa zonei
        // din care face parte si marcam zona ca vizitata pe harta
        masa = fill(p, n, i, ji);
        if (masa > masa_max) {
          coord_lin = i;
          coord_col = ji - sizeof(int);
          // intrucat am indexat de la 1 scadem primi octeti
          masa_max = masa;
        }
      }
  printf("%d %d %d", coord_lin, coord_col, masa_max);
  free_matrix(mat, n);
  return 0;
}
