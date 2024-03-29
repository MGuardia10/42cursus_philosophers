# NAME
NAME		=	philo

# SOURCE
SRC_DIR		=	src/
SRC_FILES	=	main.c \
				parsing.c \
				init_data.c \
				simulation.c \
				thread_safe_functions.c \
				actions.c \
				syncro_utils.c \
				utils.c \
				print.c \
				exit.c
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))

# OBJECTS
OBJ_DIR		=	objs/
OBJ_FILES	=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

# COMPILER
CC			=	cc
FLAGS		=	-Wall -Wextra -Werror
INC			=	-I inc
THREADS		=	-lpthread
RM			=	rm -rf

# COLORS
RED		=		\033[91;1m
GREEN	=		\033[92;1m
YELLOW	=		\033[93;1m
BLUE	=		\033[94;1m
PINK	=		\033[95;1m
CLEAR	=		\033[0m

# RULES
all:	$(NAME)

$(NAME):	$(OBJ_FILES)
	@echo "$(BLUE)Compiling philo program.$(CLEAR)"
	$(CC) $(FLAGS) $(INC) $(THREADS) $(OBJ_FILES) -o $(NAME)
	@echo "$(GREEN)[philo --> OK]\n$(CLEAR)$(GREEN)Success!$(CLEAR)\n"
	@echo "$(PINK)\tUsage: ./philo <n_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [n_times_each_philosopher_eat]"
	@echo "\t<> --> obligatory\n\t[] --> optional\n$(CLEAR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Removing compiled files.$(CLEAR)"
	$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Object files removed correctly\n$(CLEAR)"

fclean: clean
	@echo "$(BLUE)Removing binary files.$(CLEAR)"
	$(RM) $(NAME)
	@echo "$(GREEN)Object files and binary removed correctly\n$(CLEAR)"

re: fclean all

.PHONY:	all clean fclean re