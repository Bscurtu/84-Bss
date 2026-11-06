
NAME = pipeline

OBJS = pipeline.c run.c ft_strjoin.c ft_split.c
SEG_F = seg_fault.c

COMPILER = cc

CFLAGS= -Wall -Wextra -Werror

all: $(NAME)
$(NAME): $(OBJS:.c=.o)


clean:
	$(RM) *.o
fclean: clean
	rm $(NAME) $(OTHER) seg_fault
re: fclean all

seg_fault: $(OTHER)
$(OTHER): $(OTHER:.c=.o)

.PHONY: all clean fclean re