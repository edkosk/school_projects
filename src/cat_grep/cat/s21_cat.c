#include "s21_cat.h"

int main(int argc, char *argv[]) {
  cat(argc, argv);
  return 0;
}

void cat(int argc, char *argv[]) {
  int option = 0;
  FILE *file;
  if (argc == 1) {
    print_file(stdin);
  } else {
    for (int i = 1; i < argc; i++) {
      if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--number") == 0) {
        option = 1;
      } else if (strcmp(argv[i], "-b") == 0 ||
                 strcmp(argv[i], "--number-nonblank") == 0) {
        option = 2;
      } else if (strcmp(argv[i], "-E") == 0 ||
                 strcmp(argv[i], "--show-ends") == 0 ||
                 strcmp(argv[i], "-vE") == 0 || strcmp(argv[i], "-e") == 0) {
        option = 3;
      } else if (strcmp(argv[i], "-T") == 0 ||
                 strcmp(argv[i], "--show-tabs") == 0 ||
                 strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "-vT") == 0) {
        option = 4;
      } else if (strcmp(argv[i], "-s") == 0 ||
                 strcmp(argv[i], "--squeeze-blank") == 0) {
        option = 5;
      } else if (strcmp(argv[i], "-v") == 0) {
        option = 6;
      } else {
        file = fopen(argv[i], "r");
        if (file == NULL) {
          printf("cat: %s: No such file or directory", argv[i]);
          continue;
        }
        if (option == 1) {
          print_number(file);
        } else if (option == 2) {
          print_nonblank(file);
        } else if (option == 3) {
          print_end(file);
        } else if (option == 4) {
          print_tab(file);
        } else if (option == 5) {
          print_squeeze(file);
        } else if (option == 6) {
          show_nonprinting(file);
        } else {
          print_file(file);
        }
        fclose(file);
      }
    }
  }
}

void print(FILE *file, int mode) {
  char *line = NULL;
  size_t len = 0;
  static int line_number = 1;
  int empty_line = 0;
  while (getline(&line, &len, file) != -1) {
    if (mode == 0) {
      printf("%s", line);
    } else if (mode == 1) {
      printf("%6d\t%s", line_number, line);
      line_number++;
    } else if (mode == 3) {
      if (line[0] == '\n') {
        if (empty_line == 0) {
          printf("%s", line);
          empty_line = 1;
        }
      } else {
        printf("%s", line);
        empty_line = 0;
      }
    }
  }
  free(line);
}

void print_file(FILE *file) { print(file, 0); }

void print_number(FILE *file) { print(file, 1); }

void print_nonblank(FILE *file) {
  char ch;
  int emptyLine = 1;
  int line_number = 1;
  while ((ch = fgetc(file)) != EOF) {
    if (emptyLine && (ch == '\n')) {
      putchar(ch);
      continue;
    } else if (emptyLine) {
      emptyLine = 0;
      printf("%6d\t", line_number++);
    }

    putchar(ch);

    if (ch == '\n') {
      emptyLine = 1;
    }
  }
}

void print_squeeze(FILE *file) { print(file, 3); }

void print_end(FILE *file) {
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      printf("$");
      printf("\n");
    } else {
      putchar(c);
    }
  }
}

void print_tab(FILE *file) {
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\t') {
      printf("^I");
    } else {
      putchar(c);
    }
  }
}

void show_nonprinting(FILE *file) {
  int c;
  while ((c = fgetc(file)) != EOF) {
    if (c >= 32 && c <= 126) {
      putchar(c);
    } else {
      printf("^%c", (c + 64));
    }
  }
}