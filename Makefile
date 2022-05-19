TARGET      	= simulate.out
SRCS        	= 1dim_fem.c utility.c simulate.c
OBJS        	= $(SRCS:.c=.o)
CC          	= gcc
CFLAG       	= -g -Wall
LIBS			= -lm

TEST_TARGET		= test.out
TEST_SRCS		= test.cpp 1dim_fem.c utility.c
TEST_OBJS		= $(TEST_SRCS:.c=.o)
PP				= clang++
CPPFLAGS		= -I$(CPPUTEST_HOME)/include
LD_LIBRARIES	= -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt

PODBASIS_NEEDS	= SNAPSHOT PARAMETERS
PODBASIS_DIR	= ./PODBASIS_EXTRACTION
PODBASIS_TARGET = ROM_PROCEDURES

EVALUEATE_NEEDS	= $(PODBASIS_DIR)/OUTPUT/02_Vk

PYTHON			= python
EVALUEATE_TARGET= evaluate_basis.py

OUTPUTS			= SNAPSHOT PARAMETERS OUTPUTALL.csv error_values.csv basis_mode.png error.png
SAVE_OUTPUTS	= 02_Vk basis_mode.png error_values.csv error.png OUTPUTALL.csv SETTINGS
SAVE_DIR		= ./result


$(TARGET):  $(OBJS)
			$(CC) $(OBJS) -o $(TARGET) $(LIBS)

exec_simulate:
			./simulate.out

test:		$(TEST_OBJS)
			$(PP) $(TEST_OBJS) -o $(TEST_TARGET) $(CPPFLAGS) $(LD_LIBRARIES)

pre_podbasis:
			cp $(PODBASIS_NEEDS) $(PODBASIS_DIR)

podbasis:	
			cd $(PODBASIS_DIR); ./$(PODBASIS_TARGET)

pre_evalueate:
			cp $(EVALUEATE_NEEDS) ./

evaluate:
			$(PYTHON) $(EVALUEATE_TARGET)

save_result:
			cp $(SAVE_OUTPUTS) $(SAVE_DIR)

all:		$(TARGET) exec_simulate pre_podbasis podbasis pre_evalueate evaluate save_result

.c.o:
			$(CC) -c $< -o $@

clean:
			rm -f $(OBJS)

fclean:     clean
			rm -f $(TARGET)
			rm -f $(TEST_TARGET)
			rm -f $(OUTPUTS)

re:         fclean all
