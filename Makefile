CC = g++
LEX = flex
BISON = bison
CFLAGS = -std=c++17

all: lexer.tab.cpp parser.tab.cpp ast.cpp function.cpp environment.cpp builtin.cpp callable.hpp
	$(CC) $(CFLAGS) lexer.tab.cpp parser.tab.cpp ast.cpp function.cpp environment.cpp builtin.cpp -o clm

lexer.tab.cpp: lexer.l
	$(LEX) -o lexer.tab.cpp lexer.l

parser.tab.cpp: parser.y
	$(BISON) -Wcounterexamples -d -o parser.tab.cpp parser.y

run-tests: all
	@echo "Running tests...\n"
	@for test in tests/t*.cl2; do \
		echo "Running $$test..."; \
		./clm < $$test; \
		echo " "; \
	done

clean:
	rm -f lexer.tab.cpp parser.tab.cpp parser.tab.hpp clm

