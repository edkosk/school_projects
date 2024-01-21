#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cat(int argc, char *argv[]);
void print_file(FILE *file);
void print_number(FILE *file);
void print_end(FILE *file);
void print_nonblank(FILE *file);
void print_tab(FILE *file);
void print_squeeze(FILE *file);
void print(FILE *file, int mode);
void show_nonprinting(FILE *file);

#endif