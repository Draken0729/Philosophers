NAME = libftprintf.a
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c ft_print_pointer.c ft_print_utils.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		 ar rc $(NAME) $(OBJ)

%.o: %.c	
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJ)
fclean: clean
	rm -f $(NAME)
re: fclean all