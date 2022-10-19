CC=g++ -std=c++17
CFLAG=-c -Wall -Werror -Wextra -pedantic
GTESTFLAGS=-lgtest

all: clean matrix_oop.a test

matrix_oop.o:
	$(CC) $(CFLAG) matrix_oop.cc -o matrix_oop.o

test.o: clean matrix_oop.a
	$(CC) $(CFLAG) test.cc -o test.o
	$(CC) matrix_oop.a test.o -o test $(GTESTFLAGS)

matrix_oop.a: matrix_oop.o
	ar rcs matrix_oop.a matrix_oop.o

test: test.o
	./test

clean:
	rm -rf *.a *.o test *.dSYM *.gc* *.out report *.info

gcov_report: test.o
	$(CC) --coverage matrix_oop.cc test.cc -o test $(GTESTFLAGS)
	./test
	lcov -t "test" -c -d . -o test_initial.info
	lcov --remove test_initial.info -o test.info '/usr/local/*' '*v1*'
	genhtml test.info -o report
	open -a "Google Chrome" report/index.html

check: test.o
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cc *.cc
	python3 ../materials/linters/cpplint.py --extensions=h *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.cc
	CK_FORK=no leaks --atExit -- ./test
	rm -rf CPPLINT.cfg