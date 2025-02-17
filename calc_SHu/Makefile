PROJECT_NAME = my_smartcalc
FLAGS = -Wall -Wextra -Werror -std=c11
CHECKFLAG = -lcheck

all: test install

$(PROJECT_NAME).a:
	gcc -c $(FLAGS) $(PROJECT_NAME).c
	ar rcs $(PROJECT_NAME).a $(PROJECT_NAME).o
	ranlib $(PROJECT_NAME).a
install: clean
	-mkdir -p build
	cd build; qmake ../project_calc/calc_giantjen/calc_giantjen.pro && make && rm -f Makefile
uninstall:
	rm -rf build*
dist: clean uninstall
	tar -czf SmartCalc_v1.tar.gz ./*
test_calc.o:
	checkmk *.check > $(PROJECT_NAME)_tests.c
	gcc $(FLAGS) -c $(PROJECT_NAME)_tests.c -o my_smartcalc_tests.o

test: clean $(PROJECT_NAME).a test_calc.o
	gcc $(FLAGS) $(CHECKFLAG) $(PROJECT_NAME).a $(PROJECT_NAME)_tests.c -o s21_test
	./s21_test

gcov_report: 
	gcc -c $(FLAGS) $(PROJECT_NAME)_tests.c
	gcc $(FLAGS) --coverage $(CHECKFLAG) $(PROJECT_NAME).c $(PROJECT_NAME)_tests.o -o s21_test
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open report/index.html

clean: 
	rm -rf *.o *.a *.gcno *.gcda *.info s21_test my_smartcalc_tests.c otchet/latex otchet/html  report *.out

format:
	clang-format -style=google -n --verbose *.c *.h project_calc/calc_giantjen/*.cpp project_calc/calc_giantjen/*.h

my_target:
	gcc $(FLAGS) main.c my_smartcalc.c credit.c
	./a.out
dvi: 
	cd otchet/ && doxygen Doxyfile && cd ..
leaks:
	CK_FORK=no leaks --atExit -- ./s21_test