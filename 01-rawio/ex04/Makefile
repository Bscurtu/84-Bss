
NAME = mls

OBJS = mls.c parse_input.c extras.c open_dir.c output_files.c parse_input.c sort.c extract_info.c

COMPILER = cc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)
$(NAME): mls.o parse_input.o extras.o open_dir.o output_files.o parse_input.o sort.o extract_info.o
clean:
	$(RM) *.o
fclean: clean
	rm $(NAME)
re: fclean all

.PHONY: all clean fclean re