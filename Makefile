TARGET      	= simulate.out
TEST_TARGET		= test.out
SRCS        	= 1dim_fem.c utility.c simulate.c
TEST_SRCS		= test.cpp 1dim_fem.c utility.c
OBJS        	= $(SRCS:.c=.o)
TEST_OBJS		= $(TEST_SRCS:.c=.o)
CC          	= gcc
CFLAG       	= -g -Wall
PP				= clang++
CPPFLAGS		= -I$(CPPUTEST_HOME)/include
LD_LIBRARIES	= -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
LIBS			= -lm

$(TARGET):  $(OBJS)
			$(CC) $(OBJS) -o $(TARGET) $(LIBS)

test:		$(TEST_OBJS)
			$(PP) $(TEST_OBJS) -o $(TEST_TARGET) $(CPPFLAGS) $(LD_LIBRARIES)

all:        $(TARGET) test

.c.o:
			$(CC) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:     clean
			rm -f $(TARGET)
			rm -f $(TEST_TARGET)

re:         fclean all
