
NAME = mcat

OBJS = mcat.c

COMPILER = cc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)
$(NAME): mcat.o
clean:
	$(RM) *.o
fclean: clean
	rm $(NAME)
re: fclean all

.PHONY: all clean fclean re