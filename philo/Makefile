# -------------------------------COLORS-------------------------------

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[1;35m
RESET = \033[0m

# ------------------------------VARIABLES------------------------------

NAME = philo

CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror -g -fsanitize=thread

RM = rm -f
MAKE = make --no-print-directory

SRCS = srcs/main.c \
		srcs/init.c \
		srcs/simulation.c \
		srcs/utils.c

S_OBJS = $(SRCS:.c=.o)

# -------------------------------RULES---------------------------------

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(S_OBJS)
	@$(CC) $(CFLAGS) $(S_OBJS) -o $(NAME) -I.
	@printf "$(GREEN)	Executable ./$(NAME) was created.\n$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I.
	@printf "$(PURPLE)	Compiled$(RESET) $<\n"

clean:
	@$(RM) $(S_OBJS)
	@printf "$(RED)	Object files were removed.\n$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)	Executable ./$(NAME) was removed.\n$(RESET)"
	@clear

re: fclean all
