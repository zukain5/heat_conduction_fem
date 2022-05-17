TARGET      = simulate.out
SRCS        = 1dim_fem.c utility.c simulate.c
OBJS        = $(SRCS:.c=.o)
CC          = gcc
CFLAG       = -Wall

$(TARGET):  $(OBJS)
			$(CC) $(OBJS) -o $(TARGET)

all:        $(TARGET)

.c.o:
			$(CC) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:     clean
			rm -f $(TARGET)

re:         fclean all
