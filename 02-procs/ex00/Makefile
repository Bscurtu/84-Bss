
NAME = family

OBJS = family.c

COMPILER = cc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(OBJS:.c=.o)
clean:
	$(RM) *.o
fclean: clean
	rm $(NAME)
re: fclean all

.PHONY: all clean fclean re