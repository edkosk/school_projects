FLAGS = -Wall -Werror -Wextra

all: s21_grep

s21_grep: s21_grep.c s21_grep.h
	gcc $(FLAGS) s21_grep.c -o s21_grep

rebuild:
	make clean
	make all

clean:
	rm -f s21_grep