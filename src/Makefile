.PHONY: all s21_string.a

CC=gcc
FLAGS=-std=c11 -g -Wall -Werror -Wextra
S21_STRING_C=s21_*.c
S21_STRING_H=s21_*.h
S21_STRING_O=s21_*.o
TESTS=tests

all: s21_string.a

s21_string.a:
	$(CC) $(S21_STRING_C) -c $(FLAGS)
	ar rc s21_string.a $(S21_STRING_O)
	ranlib s21_string.a

s21_covered:
	$(CC) $(S21_STRING_C) -c -lcheck $(FLAGS) --coverage
	ar rc s21_string.a $(S21_STRING_O)
	ranlib s21_string.a

style:
	clang-format -style=google -i *.c *h

test: clean s21_covered
	$(CC) $(TESTS)*.c -c -lcheck $(FLAGS) --coverage
	$(CC) $(TESTS)*.o s21_string.a -o $(TESTS) -lcheck --coverage $(FLAGS) -lsubunit -lm -lgcov

clean:
	rm -rf $(TESTS) *.a *.o *.gcda *.gcno *.gcov *.info *.html report

rebuild: clean all

gcov_report: test
	./$(TESTS)
	lcov -t "s21_string" -o s21_string.info -c -d .
	genhtml -o report s21_string.info
	open report/index.html
