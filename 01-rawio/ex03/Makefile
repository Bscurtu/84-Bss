
NAME = mtail

OBJS = extras.c open_file.c args.c print_lines.c reader.c  mtail.c pipe.c

COMPILER = cc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)
$(NAME): extras.o open_file.o args.o print_lines.o reader.o mtail.o pipe.c
clean:
	$(RM) *.o
fclean: clean
	rm $(NAME)
re: fclean all

.PHONY: all clean fclean re