CC = gcc
OPTIONS = -Wall -W -g -std=c89 -pedantic -O3

SRC_DIR = ./src
HED_DIR = ./inc
OBJ_DIR = ./obj

SRC = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
INC = -I$(HED_DIR)

EXEC = huffman-compressor

build:
	@mkdir -p $(OBJ_DIR)
	@echo - Building...
	@$(MAKE) $(EXEC) --no-print-directory
	@echo - Done

$(EXEC): $(OBJ)
	@echo + Linking...
	@$(CC) $(OPTIONS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo + + Compiling "$(notdir $<)"
	@$(CC) -o $@ -c $(OPTIONS) $(INC) $<

clean:
	@rm -rf $(OBJ_DIR) $(EXEC)

rebuild:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) build --no-print-directory

.PHONY: build clean rebuild