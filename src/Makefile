CC = g++

SOURCES = matrix.cc
LIB = matrix_oop.a

SOURCE_TEST = matrix_test.cc
OUT_TEST = matrix_test

OS=$(shell uname)
ifeq ($(OS), Linux)
CPPFLAGS_TEST = -lgtest -lpthread -lgtest_main -L/usr/lib
LEAK_CHECK = valgrind --leak-check=full -s
endif
ifeq ($(OS), Darwin)
CPPFLAGS_TEST = -lgtest -lgtest_main
LEAK_CHECK = leaks -q --atExit --
endif

all: clean $(LIB)

$(LIB): matrix.o
	@ar -rc $(LIB) *.o
	@ranlib $(LIB)
	@rm *.o

test: clean
	$(CC) $(SOURCES) $(SOURCE_TEST) $(CPPFLAGS_TEST) -o $(OUT_TEST)
	./$(OUT_TEST)

matrix.o: 
	@$(CC) -c $(SOURCES)

leaks: test
	$(LEAK_CHECK) ./$(OUT_TEST)

gcov_report: clean $(LIB)
	$(CC) --coverage $(SOURCES) $(SOURCE_TEST) -o test $(CPPFLAGS_TEST)
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info

clean:
	rm -rf ./lcov_report
	rm -rf *.o *.a *.gcno *.out *.dSYM *.gcda *.gcov *.info ./$(OUT_TEST) *.txt test ./gcov_tests report
