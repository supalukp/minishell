# **************************************************************************** #
# *                                                                          * #
# *                               MAKEFILE 🔨                                * #
# *                            ⛓️ MINISHELL 🐚                               * #
# *                                                                          * #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
FLAGS += -fsanitize=address -g

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
EXEC_DIR = execution
BUILTIN_DIR = builtin
REDIRECT_DIR = redirect
ENV_DIR = env
VPATH = . ${PARS_DIR} ${EXEC_DIR} ${BUILTIN_DIR} ${ENV_DIR} ${REDIRECT_DIR}

# **************************************************************************** #
# *********************************HEADERS************************************ #
# **************************************************************************** #

HEADERS =	${INC_DIR}/execution.h \
			${INC_DIR}/headings.h \
			${INC_DIR}/structures.h \

# **************************************************************************** #
# ********************************SRC FILES*********************************** #
# **************************************************************************** #

FILES = main.c \
		${PARS_DIR}/ast_parsing.c \
		${PARS_DIR}/ast_separator.c \
		${PARS_DIR}/ast_parenthesis.c \
		${PARS_DIR}/cmd_line.c \
		${PARS_DIR}/cmd_redirections.c \
		${PARS_DIR}/cmd_elements.c \
		${PARS_DIR}/cmd_ll_files.c \
		${PARS_DIR}/visual.c \
		${PARS_DIR}/clean.c \
		${EXEC_DIR}/my_tree.c \
		${EXEC_DIR}/execution.c \
		${EXEC_DIR}/exec_utils.c \
		${EXEC_DIR}/multi_pipe.c \
		${EXEC_DIR}/pipes_init.c \
		${EXEC_DIR}/pipes_utils.c \
		${EXEC_DIR}/single_cmd.c \
		${EXEC_DIR}/set_io.c \
		${EXEC_DIR}/pipes_cmd_lst.c \
		${REDIRECT_DIR}/redirect.c \
		${EXEC_DIR}/error_msg.c \
		${REDIRECT_DIR}/heredoc.c \
		${BUILTIN_DIR}/builtin_utils.c \
		${BUILTIN_DIR}/ft_echo.c \
		${BUILTIN_DIR}/ft_pwd.c \
		${BUILTIN_DIR}/ft_env.c \
		${BUILTIN_DIR}/ft_export.c \
		${BUILTIN_DIR}/ft_export_utils.c \
		${BUILTIN_DIR}/ft_export_no_args.c \
		${BUILTIN_DIR}/ft_export_valid_key.c \
		${BUILTIN_DIR}/ft_export_modify_lst.c \
		${BUILTIN_DIR}/ft_unset.c \
		${ENV_DIR}/env_init.c \
		${ENV_DIR}/env_utils.c \
		${ENV_DIR}/env_convert.c


OBJ = $(patsubst %.c,build/%.o,$(notdir $(FILES)))

# OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

# **************************************************************************** #
# **********************************MAKE************************************** #
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	@make -C libft --no-print-directory
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a -lreadline
	@echo -n "$(COLOUR_BRIGHT_GREEN)Loading: "
	@i=1; \
	while [ $$i -le 25 ]; do \
		echo -n "█"; \
		i=$$((i + 1)); \
		sleep 0.01; \
	done
	@echo " 100% $(COLOUR_END)🎆"
	@echo "🤖$(COLOUR_PURPLE) $(NAME) 🤖         $(COLOUR_GREEN)PROGRAM CREATED ✅$(COLOUR_END)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: %.c $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	if [ -d "$(OBJ_DIR)" ]; then rm -r $(OBJ_DIR); fi
	@make -C libft clean --no-print-directory
	@rm -f ${OBJ}
	@echo "🤖 $(COLOUR_PURPLE)$(NAME) 🤖$(COLOUR_CYAN)    EXTRA FILES REMOVED. $(COLOUR_END)🗑️"

fclean: clean
	@make -C libft fclean --no-print-directory
	@rm -f ${NAME}
	@echo "$(COLOUR_PURPLE)🤖 $(NAME) 🤖 $(COLOUR_RED)     PROGRAM BULLDOZED. $(COLOUR_END)💣"

re: fclean all

.PHONY: all clean fclean re