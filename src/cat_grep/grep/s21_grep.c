#include "s21_grep.h"

int main(int argc, char *argv[]) {
  grep(argc, argv);
  return 0;
}

void grep(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: grep [OPTION]... PATTERNS [FILE]...");
  } else if (strcmp(argv[1], "-i") == 0) {
    ignore(argc, argv);
  } else if (strcmp(argv[1], "-v") == 0) {
    invert(argc, argv);
  } else if (strcmp(argv[1], "-c") == 0) {
    counter(argc, argv);
  } else if (strcmp(argv[1], "-n") == 0) {
    number(argc, argv);
  } else if (strcmp(argv[1], "-e") == 0 || strcmp(argv[1], "-E") == 0) {
    pattern(argc, argv);
  } else if (strcmp(argv[1], "-l") == 0) {
    files_w_matches(argc, argv);
  } else if (strcmp(argv[1], "-h") == 0) {
    no_filename(argc, argv);
  } else if (strcmp(argv[1], "-s") == 0) {
    no_message(argc, argv);
  } else if (strcmp(argv[1], "-o") == 0) {
    only_matches(argc, argv);
  } else if (strcmp(argv[1], "-f") == 0) {
    file(argc, argv);
  } else if (strcmp(argv[1], "-iv") == 0) {
    ignore_invert(argc, argv);
  } else if (strcmp(argv[1], "-in") == 0) {
    ignore_number(argc, argv);
  } else {
    read(argc, argv);
  }
}

void read(int argc, char *argv[]) {
  regex_t regex;
  int ret;
  if ((ret = regcomp(&regex, argv[1], REG_EXTENDED)) != 0) {
    char error_message[100];
    regerror(ret, &regex, error_message, 100);
    fprintf(stderr, REG_ERROR, error_message);
  } else {
    for (int i = 2; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, ERROR, argv[i]);
        continue;
      }
      char *line = NULL;
      size_t len = 0;
      while (getline(&line, &len, file) != -1) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
          if (argc == 3)
            printf("%s", line);
          else
            printf("%s:%s", argv[i], line);
        }
      }
      free(line);
      fclose(file);
    }
    regfree(&regex);
  }
}

void all_extend(int argc, char *argv[], int mode, int no_name) {
  regex_t regex;
  int ret;
  if ((ret = regcomp(&regex, argv[2], REG_EXTENDED)) != 0) {
    char error_message[100];
    regerror(ret, &regex, error_message, 100);
    fprintf(stderr, REG_ERROR, error_message);
  } else {
    for (int i = 3; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        if (mode != 14) {
          fprintf(stderr, ERROR, argv[i]);
          continue;
        } else {
          continue;
        }
      }
      char *line = NULL;
      size_t len = 0;
      int line_number = 1, found = 0;
      while (getline(&line, &len, file) != -1 && !found) {
        if ((regexec(&regex, line, 0, NULL, 0) == 0 && mode == 0) ||
            (regexec(&regex, line, 0, NULL, 0) == 0 && mode == 4)) {
          if ((argc == 4) || no_name == 1)
            printf("%s", line);
          else
            printf("%s:%s", argv[i], line);
        } else if (regexec(&regex, line, 0, NULL, 0) != 0 && mode == 1) {
          if (argc == 4)
            printf("%s", line);
          else
            printf("%s:%s", argv[i], line);
        } else if (regexec(&regex, line, 0, NULL, 0) == 0 && mode == 2) {
          if (argc > 4)
            printf("%s:%d:%s", argv[i], line_number, line);
          else
            printf("%d:%s", line_number, line);
        } else if (regexec(&regex, line, 0, NULL, 0) == 0 && mode == 3) {
          printf("%s\n", argv[i]);
          found = 1;
        }
        line_number++;
      }
      free(line);
      fclose(file);
    }
    regfree(&regex);
  }
}

void invert(int argc, char *argv[]) { all_extend(argc, argv, 1, 0); }

void number(int argc, char *argv[]) { all_extend(argc, argv, 2, 0); }

void pattern(int argc, char *argv[]) { all_extend(argc, argv, 0, 0); }

void files_w_matches(int argc, char *argv[]) { all_extend(argc, argv, 3, 0); }

void no_filename(int argc, char *argv[]) { all_extend(argc, argv, 0, 1); }

void no_message(int argc, char *argv[]) { all_extend(argc, argv, 4, 0); }

void counter(int argc, char *argv[]) {
  regex_t regex;
  int ret;
  if ((ret = regcomp(&regex, argv[2], REG_EXTENDED)) != 0) {
    char error_message[100];
    regerror(ret, &regex, error_message, 100);
    fprintf(stderr, REG_ERROR, error_message);
  } else {
    for (int i = 3; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, ERROR, argv[i]);
        continue;
      }
      char *line = NULL;
      size_t len = 0;
      int count = 0;
      while (getline(&line, &len, file) != -1) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
          count++;
        }
      }
      if (count >= 0) {
        if (argc > 4)
          printf("%s:%d\n", argv[i], count);
        else
          printf("%d\n", count);
      }
      free(line);
      fclose(file);
    }
    regfree(&regex);
  }
}

void only_matches(int argc, char *argv[]) {
  regex_t regex;
  int ret;
  if ((ret = regcomp(&regex, argv[2], REG_EXTENDED)) != 0) {
    char error_message[100];
    regerror(ret, &regex, error_message, 100);
    fprintf(stderr, "%s\n", error_message);
  } else {
    for (int i = 3; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", argv[i]);
        continue;
      }
      char *line = NULL;
      size_t len = 0;
      while (getline(&line, &len, file) != -1) {
        regmatch_t match;
        int offset = 0;
        while (regexec(&regex, line + offset, 1, &match, 0) == 0) {
          if (argc == 4) {
            printf("%.*s\n", (int)(match.rm_eo - match.rm_so),
                   line + offset + match.rm_so);
            offset += match.rm_eo;
          } else {
            printf("%s:%.*s\n", argv[i], (int)(match.rm_eo - match.rm_so),
                   line + offset + match.rm_so);
            offset += match.rm_eo;
          }
        }
      }
      free(line);
      fclose(file);
    }
    regfree(&regex);
  }
}

void all_ignore(int argc, char *argv[], int mode) {
  regex_t regex;
  int ret;
  if ((ret = regcomp(&regex, argv[2], REG_ICASE)) != 0) {
    char error_message[100];
    regerror(ret, &regex, error_message, 100);
    fprintf(stderr, REG_ERROR, error_message);
  } else {
    for (int i = 3; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, ERROR, argv[i]);
        continue;
      }
      char *line = NULL;
      size_t len = 0;
      int line_number = 1;
      while (getline(&line, &len, file) != -1) {
        if (regexec(&regex, line, 0, NULL, 0) == 0 && mode == 00) {
          if (argc == 4)
            printf("%s", line);
          else
            printf("%s: %s", argv[i], line);
        } else if (regexec(&regex, line, 0, NULL, 0) != 0 && mode == 01) {
          if (argc == 4)
            printf("%s", line);
          else
            printf("%s:%s", argv[i], line);
        } else if (regexec(&regex, line, 0, NULL, 0) == 0 && mode == 10) {
          if (argc > 4)
            printf("%s:%d:%s", argv[i], line_number, line);
          else
            printf("%d:%s", line_number, line);
        }
        line_number++;
      }

      free(line);
      fclose(file);
    }
    regfree(&regex);
  }
}

void ignore(int argc, char *argv[]) { all_ignore(argc, argv, 00); }

void ignore_invert(int argc, char *argv[]) { all_ignore(argc, argv, 01); }

void ignore_number(int argc, char *argv[]) { all_ignore(argc, argv, 10); }

void file(int argc, char *argv[]) {
  size_t pattern_len = 0;
  regex_t regex;
  FILE *pattern_file = fopen(argv[2], "r");
  if (pattern_file == NULL) {
    fprintf(stderr, ERROR, argv[2]);
  }
  char *pattern_line = NULL;
  while (getline(&pattern_line, &pattern_len, pattern_file) != -1) {
    regcomp(&regex, pattern_line, REG_EXTENDED);
    for (int i = 3; i < argc; i++) {
      FILE *file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, ERROR, argv[i]);
        continue;
      }
      char *line = NULL;
      size_t len = 0;
      while (getline(&line, &len, file) != -1) {
        if (regexec(&regex, line, 0, NULL, 0) == 0) {
          if (argc == 4)
            printf("%s", line);
          else
            printf("%s: %s", argv[i], line);
        }
      }
      free(line);
      fclose(file);
    }
    regfree(&regex);
  }
}