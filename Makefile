# **************************************************************************** #
# *                                                                          * #
# *                               MAKEFILE 🔨                                * #
# *                            ⛓️ MINISHELL 🐚                               * #
# *                                                                          * #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
CFLAGS += -lreadline

# **************************************************************************** #
# **********************************COLORS************************************ #
# **************************************************************************** #

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m
COLOUR_BLACK=\033[0;30m
COLOUR_YELLOW=\033[0;33m
COLOUR_PURPLE=\033[0;35m
COLOUR_CYAN=\033[0;36m

COLOUR_BRIGHT_BLACK=\033[1;30m
COLOUR_BRIGHT_RED=\033[1;31m
COLOUR_BRIGHT_GREEN=\033[1;32m
COLOUR_BRIGHT_YELLOW=\033[1;33m
COLOUR_BRIGHT_BLUE=\033[1;34m
COLOUR_BRIGHT_PURPLE=\033[1;35m
COLOUR_BRIGHT_CYAN=\033[1;36m

# **************************************************************************** #
# *******************************DIRECTORIES********************************** #
# **************************************************************************** #

OBJ_DIR = build
INC_DIR = inc
PARS_DIR = parsing

# **************************************************************************** #
# *********************************HEADERS************************************ #
# **************************************************************************** #

HEADERS =	${INC_DIR}/functions.h \
			${INC_DIR}/headings.h \
			${INC_DIR}/structures.h \

# **************************************************************************** #
# ********************************SRC FILES*********************************** #
# **************************************************************************** #

FILES = main.c \
		# ${PARS_DIR}/sort.c \
		# ${PARS_DIR}/forward.c \
		# ${PARS_DIR}/back.c \
		# ${PARS_DIR}/back_up.c \
		# ${PARS_DIR}/back_down.c \
		# ${PARS_DIR}/funct_choice.c \
		# ${PARS_DIR}/view.c \
		# ${PARS_DIR}/push.c \
		# ${PARS_DIR}/rotate.c \
		# ${PARS_DIR}/swap.c \
		# ${PARS_DIR}/free.c \
		# ${PARS_DIR}/optimize_funct.c \

OBJ = ${FILES:$(PARS_DIR)/%.c=$(OBJ_DIR)/%.o}

# **************************************************************************** #
# **********************************MAKE************************************** #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	make -C libft --no-print-directory
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a
	@echo -n "$(COLOUR_BRIGHT_GREEN)Loading: "
	@i=1; \
	while [ $$i -le 25 ]; do \
		echo -n "█"; \
		i=$$((i + 1)); \
		sleep 0.05; \
	done
	@echo " 100% $(COLOUR_END)🎆"
	@echo "🤖$(COLOUR_PURPLE) $(NAME) 🤖         $(COLOUR_GREEN)PROGRAM CREATED ✅$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(OBJ_DIR)" ]; then rm -r $(OBJ_DIR); fi
	make -C libft clean --no-print-directory
	rm -f ${OBJ}
	@echo "🤖 $(COLOUR_PURPLE)$(NAME) 🤖$(COLOUR_CYAN)    EXTRA FILES REMOVED. $(COLOUR_END)🗑️"

fclean: clean
	make -C libft fclean --no-print-directory
	rm -f ${NAME}
	@echo "$(COLOUR_PURPLE)🤖 $(NAME) 🤖 $(COLOUR_RED)     PROGRAM BULLDOZED. $(COLOUR_END)💣"

re: fclean all

.PHONY: all clean fclean re