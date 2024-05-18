NAME = philo.a
CC = cc
CFLAGS = 
SRCS = ./src/philo.c\
	./src/parsing.c\
	./src/utils.c\
	./src/utils_2.c\
	./src/routine.c\

OBJS = $(SRCS:.c=.o)

all:$(NAME)
	$(CC) $(CFLAGS) ./src/philo.c ./philo.a

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS) 

clean:
	rm -f $(OBJS) $(NAME) a.out

re : clean all