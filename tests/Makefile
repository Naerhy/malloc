NAME = malloc_test

SRC = main.c
OBJ = $(SRC:%.c=%.o)
INC = ../inc
LIB = ft_malloc

CC = gcc
CFLAGS = -Wall -Werror -Wextra

RM = rm -rf

%.o: %.c
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C ..
	$(CC) -o $@ $^ -L.. -l$(LIB)

all: $(NAME)

clean:
	$(MAKE) clean -C ..
	$(RM) $(OBJ)

fclean: clean
	$(MAKE) fclean -C ..
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
