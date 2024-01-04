NAME = tests

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = ../inc
LIB_DIR = ..

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
LIB = ft_malloc

CC = gcc
CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C ..
	$(CC) -o $@ $^ -L$(LIB_DIR) -l$(LIB) -Wl,-rpath,$(LIB_DIR)

$(OBJ_DIR):
	mkdir -p $@

all: $(NAME)

clean:
	$(MAKE) clean -C ..
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C ..
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
