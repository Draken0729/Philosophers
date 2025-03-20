NAME = philo.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

FT_PRINTF_DIR = ft_printf

SRCS = main.c utils.c init.c philo.c actions.c $(FT_PRINTF_DIR)/ft_printf.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
