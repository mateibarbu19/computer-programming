// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#include <commands.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void create(char *comenzi) {
  FILE *files_info, *usermap, *archive, *file;
  char archive_name[NAMSIZ], path[NAMSIZ];
  union record obiect;
  int number_uid, number_gid;
  char line[RECORDSIZE + 1], *p;

  strcpy(archive_name, p = get_parameter(comenzi, 1));
  free(p);

  strcpy(path, p = get_parameter(comenzi, 2));
  free(p);

  // daca apar erori in lucrul cu fisierele inseamna ca programul a esuat
  p = strchr(archive_name, '.');
  if (p == NULL || strcmp(p, ".tar") != 0) {
    printf("> Failed!\n");
    return;
  }
  files_info = open_dir_file(path, "files.txt", "r");
  if (files_info == NULL) {
    printf("> Failed!\n");
    return;
  }
  usermap = open_dir_file(path, "usermap.txt", "r");
  if (usermap == NULL) {
    printf("> Failed!\n");
    return;
  }
  archive = fopen(archive_name, "wb");
  if (archive == NULL) {
    printf("> Failed!\n");
    return;
  }

  while (fgets(line, RECORDSIZE + 1, files_info) != NULL) {
    // citim linie cu linie din fisier
    // si procesam fiecare camp in parte
    line[strlen(line) - 1] = '\0';
    memset(&obiect.header, 0, RECORDSIZE);

    p = strtok(line, " "); // permissions
    set_mode(obiect.header.mode, p);

    p = strtok(NULL, " "); // no_links

    p = strtok(NULL, " "); // uid
    strcpy(obiect.header.uname, p);
    number_uid = find_id(usermap, obiect.header.uname, 1);
    if (number_uid == -1) {
      printf("> Failed!\n");
      fclose(archive);
      return;
    }
    write_octal(obiect.header.uid, number_uid, 8);

    p = strtok(NULL, " "); // gid
    strcpy(obiect.header.gname, p);
    number_gid = find_id(usermap, obiect.header.gname, 2);
    if (number_gid == -1) {
      printf("> Failed!\n");
      fclose(archive);
      return;
    }
    write_octal(obiect.header.gid, number_gid, 8);

    p = strtok(NULL, " "); // size
    write_octal(obiect.header.size, atol(p), 12);

    set_time(obiect.header.mtime, p);

    p = strtok(NULL, " "); // citim numele fisierului
    strcpy(obiect.header.name, p);
    strcpy(obiect.header.linkname, p);
    file = open_dir_file(path, obiect.header.name, "rb");
    if (file == NULL) {
      printf("> Failed!\n");
      fclose(archive);
      return;
    }

    strcpy(obiect.header.magic, "GNUtar ");
    obiect.header.typeflag = '0';
    strcpy(obiect.header.devmajor, "0000000");
    strcpy(obiect.header.devminor, "0000000");
    memset(obiect.header.chksum, ' ', 8);
    write_octal(obiect.header.chksum, chksum(obiect.charptr), 7);

    add_file_to_tar(archive, obiect.charptr, file);
    // completam cu '\0' pana la un multiplu de 512 bytes

    fclose(file);
  }
  // mai completam cu inca un bloc de 512 gol
  memset(line, '\0', RECORDSIZE);
  fwrite(line, sizeof(char), RECORDSIZE, archive);

  printf("> Done!\n");
  fclose(archive);
  fclose(files_info);
  fclose(usermap);
}

void list(char *comenzi) {
  FILE *archive;
  char archive_name[NAMSIZ], *p;
  union record obiect;
  int size, total_size, nr;

  strcpy(archive_name, p = get_parameter(comenzi, 1));
  free(p);

  archive = fopen(archive_name, "rb");
  if (archive == NULL) {
    printf("> Failed!\n");
    return;
  }

  nr = fread(obiect.charptr, sizeof(char), RECORDSIZE, archive);
  // cat timp citim 512 octeti si fisierul exista, adica are un nume nevid
  while (nr == RECORDSIZE && obiect.header.name[0] != '\0') {
    printf("> ");
    puts(obiect.header.name);
    read_octal(obiect.header.size, &size, 12);
    total_size = size + RECORDSIZE - size % RECORDSIZE;
    // sarim peste continutul fisierului
    fseek(archive, total_size, SEEK_CUR);
    nr = fread(obiect.charptr, sizeof(char), RECORDSIZE, archive);
  }
}

void extract(char *comenzi) {
  FILE *archive, *file;
  char file_name[NAMSIZ], archive_name[NAMSIZ], buffer[RECORDSIZE], *p;
  union record obiect;
  int size, total_size, nr_blocks, i, found, nr;

  strcpy(file_name, p = get_parameter(comenzi, 1));
  free(p);

  strcpy(archive_name, p = get_parameter(comenzi, 2));
  free(p);

  archive = fopen(archive_name, "rb");
  if (archive == NULL) {
    printf("> Failed!\n");
    return;
  }

  found = 0;
  nr = fread(obiect.charptr, sizeof(char), RECORDSIZE, archive);
  // cat timp citim 512 octeti si fisierul exista, adica are un nume nevid
  while (found == 0 && nr == RECORDSIZE && obiect.header.name[0] != '\0') {
    if (strcmp(file_name, obiect.header.name) == 0) {
      found = 1;
      strcpy(buffer, "extracted_");
      strcat(buffer, file_name);
      file = fopen(buffer, "wb");
      if (file == NULL) {
        printf("> A aparut o eroare de memorie!\n");
        return;
      }
    }
    read_octal(obiect.header.size, &size, 12);
    total_size = size + RECORDSIZE - size % RECORDSIZE;
    nr_blocks = total_size / RECORDSIZE;

    if (found == 0) {
      // sarim peste continutul fisierului
      fseek(archive, total_size, SEEK_CUR);
    } else {
      // altfel copiam continutul fisierului
      for (i = 0; i < nr_blocks; i++) {
        fread(buffer, sizeof(char), RECORDSIZE, archive);
        if ((i + 1) * RECORDSIZE <= size)
          fwrite(buffer, sizeof(char), RECORDSIZE, file);
        else
          fwrite(buffer, sizeof(char), size - i * RECORDSIZE, file);
      }
    }
    nr = fread(obiect.charptr, sizeof(char), RECORDSIZE, archive);
  }
  if (found == 0)
    printf("> File not found!\n");
  if (found == 1)
    printf("> File extraced!\n");
  fclose(archive);
}

int parameter_count(char *comenzi) {
  // functia returneaza numarul de parametrii transmisi utilitarului
  char *temp = strdup(comenzi);
  char *p = strtok(temp, " ");
  int count = 0;
  while (p != NULL) {
    count++;
    p = strtok(NULL, " ");
  }
  free(temp);
  return count - 1;
}

char *get_parameter(char *comenzi, int position) {
  // functia returneaza un anumit parametru transmis utilitarului
  // parametrul de pe pozitia: position
  char *temp = strdup(comenzi);
  char *p = strtok(temp, " ");
  int count = 0;
  while (p != NULL && count < position) {
    count++;
    p = strtok(NULL, " ");
  }
  char *q = strdup(p);
  free(temp);
  return q;
}

FILE *open_dir_file(char *path, char *name, char *mode) {
  // functia deschide un fisier din folderul path
  FILE *thisfile;
  char *new_path = malloc(strlen(path) + strlen(name) + 1);
  strcpy(new_path, path);
  strcat(new_path, name);
  thisfile = fopen(new_path, mode);
  free(new_path);
  return thisfile;
}

void set_mode(char *mode, char *p) {
  // functia proceseaza permisiunile fisierului si seteaza modul pt arhiva
  memset(mode, '0', 7);
  mode[4] += convert_permissions(p + 1);
  mode[5] += convert_permissions(p + 4);
  mode[6] += convert_permissions(p + 7);
}

int convert_permissions(char *p) {
  // functia converteste permisiunile de la cifra la litera
  int sum = 0;
  if (p[0] == 'r')
    sum += 4;
  if (p[1] == 'w')
    sum += 2;
  if (p[2] == 'x')
    sum += 1;
  return sum;
}

void write_octal(char *field, long number, int n) {
  // functia scrie un numar decimal in octal cu padding
  memset(field, '0', n);
  char temp[TUNMLEN];
  sprintf(temp, "%lo", number);
  sprintf(field + n - 1 - strlen(temp), "%lo", number);
}

int find_id(FILE *usermap, char *user, int nr_column) {
  // functia cauta uid-ul sau gid-ul in fisierul files.txt si il returneaza
  // nr_column = 1, daca vrem sa aflam uid-ul
  // nr_column = 2, daca vrem sa aflam gid-ul
  int i;
  char line[RECORDSIZE + 1], *p;
  rewind(usermap); // mutam cursorul la inceputul fisierului
  while (fgets(line, RECORDSIZE + 1, usermap) != NULL) {
    // citim linie cu linie
    if (strstr(line, user) == line) {
      // daca avem informatiile despre utilizatorul nostru pe linia curenta
      // apoi sarim peste campurile care nu ne intereseaza
      p = strchr(line, ':'); // sarim mai intai peste nume
      for (i = 1; i <= nr_column; i++)
        p = strchr(p + 1, ':');
      if (p + 1 == NULL || !isdigit(p[1]))
        return -1;
      return atoi(p + 1);
    }
  }
  return -1;
}

void set_time(char *mtime, char *p) {
  int i;
  char buffer[TUNMLEN];
  buffer[0] = '\0';
  for (i = 0; i < 3; i++) {
    p = strtok(NULL, " ");
    strcat(buffer, p);
    strcat(buffer, " ");
  }
  write_octal(mtime, epoch_time(buffer), 12);
}

__time_t epoch_time(char *buffer) {
  struct tm temp;
  memset(&temp, 0, sizeof(struct tm));

  sscanf(buffer, "%d-%d-%d ", &temp.tm_year, &temp.tm_mon, &temp.tm_mday);
  sscanf(buffer + 11, "%d:%d:%d ", &temp.tm_hour, &temp.tm_min, &temp.tm_sec);
  temp.tm_year -= 1900;
  temp.tm_mon -= 1;
  temp.tm_isdst = -1;
  return mktime(&temp);
}

int chksum(char *p) {
  int sum = 0, i;
  for (i = 0; i < RECORDSIZE; i++)
    sum += p[i];
  return sum;
}

void add_file_to_tar(FILE *archive, char *charptr, FILE *file) {
  // functia scrie headerul unui fisier + continutul lui
  // in continuarea unei arhive
  char buffer[RECORDSIZE], ch;
  int i, nr;
  fwrite(charptr, sizeof(char), RECORDSIZE, archive);
  nr = fread(buffer, sizeof(char), RECORDSIZE, file);
  while (nr == RECORDSIZE) {
    fwrite(buffer, sizeof(char), RECORDSIZE, archive);
    nr = fread(buffer, sizeof(char), RECORDSIZE, file);
  }
  fwrite(buffer, sizeof(char), nr, archive);
  ch = '\0';
  for (i = nr; i < RECORDSIZE; i++)
    fwrite(&ch, sizeof(char), 1, archive);
}

void read_octal(char *field, int *number, int n) {
  // functia citeste un numar octal
  int i = 0;
  while (field[i] == '0')
    i++;
  if (i == n - 1)
    *number = 0;
  sscanf(field + i, "%o", number);
}
