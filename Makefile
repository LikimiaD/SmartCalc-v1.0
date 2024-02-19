CC = gcc
TEST_LIBS = -lcheck -lm -lpthread -lrt -lsubunit
FLAGS = -Wall -Werror -Wextra -std=c11
STACK_LIB = stack_char.c  stack_double.c
POLAND_LIB = calculate_poland.c  parse_equation.c
SOURCES = stack_char.c  stack_double.c calculate_poland.c  parse_equation.c
LIBS_A = libstack.a libpoland.a
DOCKER_VERSION = 1.0.0

all: gcov_report

stack_lib:
	for source in $(STACK_LIB); do \
		$(CC) -c $(CFLAGS) functions/$$source -o functions/$${source%.c}.o; \
	done
	ar rcs libstack.a functions/stack_char.o functions/stack_double.o
	rm -f functions/*.o

poland_lib_gcov: stack_lib
	rm -f libpoland.a
	for source in $(POLAND_LIB); do \
		$(CC) -c $(CFLAGS) functions/$$source -o functions/$${source%.c}.o; \
	done
	ar rcs libpoland.a functions/calculate_poland.o functions/parse_equation.o
	rm -f functions/*.o

poland_lib: stack_lib
	for source in $(POLAND_LIB); do \
		$(CC) -c $(CFLAGS) functions/$$source -o functions/$${source%.c}.o; \
	done
	for source in $(STACK_LIB); do \
		$(CC) -c $(CFLAGS) functions/$$source -o functions/$${source%.c}.o; \
	done
	ar rcs libpoland.a functions/calculate_poland.o functions/parse_equation.o functions/stack_char.o functions/stack_double.o
	rm -f functions/*.o

test: stack_lib poland_lib_gcov
	$(CC) $(CFLAGS) tests/*.c $(LIBS_A) $(TEST_LIBS) -o test.out && ./test.out

clean:
	rm -f *.a *.out functions/*.gcno functions/*.gcda *.gcno *.gcda *.info *.gcov *.html *.css
	rm -rf report/

gcov_flag:
	$(eval CFLAGS += -fprofile-arcs -ftest-coverage -fPIC -O0)

gcov_report: clean gcov_flag test
	mkdir -p report
	gcovr --html-details report/gcov.html

dvi:
	open ../README.md

install: poland_lib
	mkdir -p build
	cd build && qmake-qt5 ../app
	make -C build

uninstall:
	rm -rf build

dist: install
	tar


