# Compilateur
CC = gcc
OPTIONS = -Wall -Wextra

# Répertoires
SRC_DIR = ./src
HED_DIR = ./inc
OBJ_DIR = ./obj

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
INC = -I$(HED_DIR)

EXEC = huffman-compressor

build:
	@mkdir -p $(OBJ_DIR)
	@$(MAKE) $(EXEC) --no-print-directory

$(EXEC): $(OBJ)
	@$(CC) $(OPTIONS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) -o $@ -c $(OPTIONS) $(INC) $<

clean:
	@rm -rf $(OBJ_DIR) $(EXEC)

rebuild:
	@$(MAKE) clean --no-print-directory
	@$(MAKE) build --no-print-directory

.PHONY: build clean rebuild