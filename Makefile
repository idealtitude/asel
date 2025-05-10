CC = gcc
CFLAGS = -Wall -I./src
LEX = flex
YACC = bison

SRC_DIR = src
LEX_SRC = $(SRC_DIR)/lexer.l
YACC_SRC = $(SRC_DIR)/parser.y

BIN_DIR = bin
BIN_NAME = aseli
VERSION_NO ?= $(shell cat ./VERSION)
ASEL = $(BIN_DIR)/$(BIN_NAME)-$(VERSION_NO)

EX_DIR = examples
EX_FILE ?= minimal.asel
EX_RUN = $(EX_DIR)/$(EX_FILE)

LEX_OUT = $(SRC_DIR)/lexer.c
YACC_OUT = $(SRC_DIR)/parser.c
YACC_HDR = $(SRC_DIR)/parser.h
AST_SRC = $(SRC_DIR)/ast.c
MAIN_SRC = $(SRC_DIR)/main.c

.PHONY: all aseli run version clean

all: aseli

$(YACC_OUT) $(YACC_HDR): $(YACC_SRC)
	@$(YACC) -d -o $(YACC_OUT) $(YACC_SRC)

$(LEX_OUT): $(LEX_SRC) $(YACC_HDR)
	@$(LEX) -o $@ $<

aseli: $(LEX_OUT) $(YACC_OUT) $(AST_SRC) $(MAIN_SRC)
	@echo Compiling $(BIN_NAME) v$(VERSION_NO)...
	@$(CC) $(CFLAGS) -o $(ASEL) $^
	@echo Done!

run: clean aseli
	./$(ASEL) ./$(EX_RUN)

version:
	@echo $(BIN_NAME) v$(VERSION_NO)

clean:
	@rm $(BIN_DIR)/* $(SRC_DIR)/lexer.c $(SRC_DIR)/parser.c $(SRC_DIR)/parser.h
	@echo Everything cleansed!
