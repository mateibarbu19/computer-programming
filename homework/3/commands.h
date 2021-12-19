// Copyright 2019 Barbu Matei (matei.barbu1905@stud.acs.upb.ro)

#ifndef COMMANDS_H_INCLUDED
#define COMMANDS_H_INCLUDED
#include <stdio.h>

#define RECORDSIZE 512
#define NAMSIZ 100
#define TUNMLEN 32
#define TGNMLEN 32

union record {
  char charptr[RECORDSIZE];
  struct {
    char name[NAMSIZ];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag;
    char linkname[NAMSIZ];
    char magic[8];
    char uname[TUNMLEN];
    char gname[TGNMLEN];
    char devmajor[8];
    char devminor[8];
  } header;
};

void create(char *comenzi);

void list(char *comenzi);

void extract(char *comenzi);

int parameter_count(char *comenzi);

char *get_parameter(char *comenzi, int position);

FILE *open_dir_file(char *path, char *name, char *mode);

void set_mode(char *mode, char *p);

int convert_permissions(char *p);

void write_octal(char *field, long number, int n);

int find_id(FILE *usermap, char *user, int nr_column);

__time_t epoch_time(char *buffer);

int chksum(char *p);

void set_time(char *mtime, char *p);

void add_file_to_tar(FILE *archive, char *charptr, FILE *file);

void read_octal(char *field, int *number, int n);

#endif // COMMANDS_H_INCLUDED
