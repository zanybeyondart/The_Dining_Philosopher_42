NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=thread
SRC = philo.c\
	parsing.c\
	utils.c\
	routine.c\
	utils_2.c

OBJS = $(SRC:%.c=%.o)

all : $(NAME)

$(NAME) : $(OBJS)
	@ $(CC) $(CFLAGS) $(OBJS)  -o $(NAME)
	
clean :
	@ $(RM) $(OBJS)

fclean : clean
	@ $(RM) $(NAME)

re : fclean all