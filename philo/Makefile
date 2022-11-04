NAME = philo

SRCS = philo.c utils.c
HEADER = include/philo.h

OBJ = $(SRCS:.c=.o)
CC  = gcc
FLAGS =  -g3 -lpthread

all : $(NAME)

%.o  : %.c  $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(FLAGS) -o $(NAME)

clean :
	@rm -rf : $(OBJ)

fclean : clean
	@rm -rf : $(NAME)
re: fclean all

.PHONY : all clean fclean re

norm:
		norminette $(SRCS) ./include

# valgrind
# -fsanitize=address
#  -fsanitize=thread
