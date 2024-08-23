CC= g++ 
FLAGS= -Wall -Wextra -Werror
STANDART= -std=c++17
TESTFLAGS=-lgtest
TESTFILES= tests/*.cpp
LCOVFLAGS = --ignore-errors inconsistent --ignore-errors mismatch
SANITIZE=-fsanitize=address -g

all: test

test: clean
	@$(CC) $(FLAGS) $(STANDART) $(TESTFILES) -o test $(TESTFLAGS)
	@echo "\033[32mTests done \033[0m"


clang-format:
	@clang-format -i containers/*/*.h tests/*.cpp tests/*.h
	@echo "\033[32mClang-format done \033[0m"

clean:
	@rm -rf test *.gcda *.info *.gcno report sanitize Main *.dSYM
	@echo "\033[33mClean done \033[0m"

add_coverage_flag:
	$(eval FLAGS += --coverage)

gcov_report: add_coverage_flag test
	./test
	lcov -t "check" -o check.info -c -d ./  --no-external $(LCOVFLAGS)
	genhtml -o report check.info $(LCOVFLAGS)
	open report/index.html

sanitize: clean
	@$(CC) $(FLAGS) $(STANDART) $(TESTFILES) -o sanitize $(TESTFLAGS) $(SANITIZE)
	@echo "\033[32mSanitize done \033[0m"

main: clean
	@$(CC) $(FLAGS) $(STANDART) main.cpp -o Main
	@echo "\033[32mMain done \033[0m"

main_sanitize: clean
	@$(CC) $(FLAGS) $(STANDART) main.cpp -o Main $(SANITIZE)
	@echo "\033[32mMain sanitize done \033[0m"