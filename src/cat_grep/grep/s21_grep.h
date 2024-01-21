#ifndef S21_GREP_H
#define S21_GREP_H

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR "grep: %s: No such file or directory\n"
#define REG_ERROR "Regular expression error: %s\n"

void grep(int argc, char *argv[]);
void ignore(int argc, char *argv[]);
void invert(int argc, char *argv[]);
void counter(int argc, char *argv[]);
void number(int argc, char *argv[]);
void pattern(int argc, char *argv[]);
void read(int argc, char *argv[]);
void files_w_matches(int argc, char *argv[]);
void no_filename(int argc, char *argv[]);
void no_message(int argc, char *argv[]);
void only_matches(int argc, char *argv[]);
void file(int argc, char *argv[]);
void all_extend(int argc, char *argv[], int mode, int no_name);
void ignore_invert(int argc, char *argv[]);
void ignore_number(int argc, char *argv[]);
void all_ignore(int argc, char *argv[], int mode);

#endif