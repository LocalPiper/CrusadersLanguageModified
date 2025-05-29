CC = g++
LEX = flex
BISON = bison
CFLAGS = -std=c++17 -I./src
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

LEXER_SRC = $(SRC_DIR)/lexer.l
PARSER_SRC = $(SRC_DIR)/parser.y

LEXER_OUT = $(BUILD_DIR)/lexer.tab.cpp
PARSER_CPP_OUT = $(BUILD_DIR)/parser.tab.cpp
PARSER_HPP_OUT = $(BUILD_DIR)/parser.tab.hpp

SRC_FILES = $(SRC_DIR)/ast.cpp \
						$(SRC_DIR)/operations.cpp \
            $(SRC_DIR)/function.cpp \
            $(SRC_DIR)/environment.cpp \
            $(SRC_DIR)/builtin.cpp \
						$(SRC_DIR)/semantic.cpp \
						$(SRC_DIR)/ir.cpp \
						$(SRC_DIR)/optimizer.cpp \
						$(SRC_DIR)/cfg.cpp

HDR_FILES = $(SRC_DIR)/ast.hpp \
						$(SRC_DIR)/operations.hpp \
            $(SRC_DIR)/function.hpp \
            $(SRC_DIR)/environment.hpp \
            $(SRC_DIR)/builtin.hpp \
            $(SRC_DIR)/callable.hpp \
            $(SRC_DIR)/array.hpp \
            $(SRC_DIR)/value.hpp \
						$(SRC_DIR)/semantic.hpp \
						$(SRC_DIR)/ir.hpp \
						$(SRC_DIR)/ir_struct.hpp \
						$(SRC_DIR)/optimizer.hpp \
						$(SRC_DIR)/cfg.hpp

all: $(BIN_DIR)/clm

$(BIN_DIR)/clm: $(LEXER_OUT) $(PARSER_CPP_OUT) $(SRC_FILES)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) $(LEXER_OUT) $(PARSER_CPP_OUT) $(SRC_FILES) -o $(BIN_DIR)/clm

$(LEXER_OUT): $(LEXER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(LEX) -o $(LEXER_OUT) $(LEXER_SRC)

$(PARSER_CPP_OUT): $(PARSER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(BISON) -Wcounterexamples -d -o $(PARSER_CPP_OUT) $(PARSER_SRC)

run-tests: all
	@echo "Running tests..."
	@for test in tests/*.cl2; do \
		echo "Running $$test..."; \
		$(BIN_DIR)/clm < $$test; \
		echo ""; \
	done

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

.PHONY: all run-tests clean


