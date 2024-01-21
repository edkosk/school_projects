FLAGS = -Wall -Werror -Wextra

all: s21_cat

s21_cat: s21_cat.c s21_cat.h
	gcc $(FLAGS) s21_cat.c -o s21_cat

rebuild:
	make clean
	make all

clean:
	rm -f s21_cat