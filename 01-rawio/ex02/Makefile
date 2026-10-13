
NAME = mcp

OBJS = mcp.c

COMPILER = cc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)
$(NAME): mcp.o
clean:
	$(RM) *.o
fclean: clean
	rm $(NAME)
re: fclean all

.PHONY: all clean fclean re