# -------------------------------COLORS-------------------------------

RED = \033[0;31m
GREEN = \033[0;32m
PURPLE = \033[1;35m
RESET = \033[0m

# ------------------------------VARIABLES------------------------------

NAME = philo

CC = cc
CFLAGS = -pthread -Wall -Wextra -Werror

RM = rm -f
MAKE = make --no-print-directory

SRCS = sources/1_main.c \
		sources/2_initializations.c \
		sources/3_simulation_utils.c \
		sources/4_surveillance.c \
		sources/5_utils.c
S_OBJS = $(SRCS:.c=.o)

BONUS_SRCS =
B_OBJS = $(BONUS_SRCS:.c=.o)

# -------------------------------RULES---------------------------------

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(S_OBJS)
	@$(CC) $(CFLAGS) $(S_OBJS) -o $(NAME) -I.
	@printf "$(GREEN)	Executable ./$(NAME) was created.\n$(RESET)"

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I.
	@printf "$(PURPLE)	Compiling$(RESET) $<\n"

clean:
	@$(RM) $(S_OBJS)
	@printf "$(RED)	Object files were removed.\n$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	@printf "$(RED)	Executable ./$(NAME) was removed.\n$(RESET)"

re: fclean all
