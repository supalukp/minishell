# **************************************************************************** #
# *                                                                          * #
# *                               MAKEFILE 🔨                                * #
# *                            ⛓️ MINISHELL 🐚                               * #
# *                                                                          * #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

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
LIB_DIR = libft
LIBFT_NAME = libft.a
LIBFT = $(LIB_DIR)/$(LIBFT_NAME)
OBJ_DIR = build
INC_DIR = inc
PARS_DIR = parsing
EXEC_DIR = execution
BUILTIN_DIR = builtin
REDIRECT_DIR = redirect
ENV_DIR = env
SIG_DIR = signals
VPATH = . ${PARS_DIR} ${EXEC_DIR} ${BUILTIN_DIR} ${ENV_DIR} ${REDIRECT_DIR} ${SIG_DIR}

# **************************************************************************** #
# *********************************HEADERS************************************ #
# **************************************************************************** #

HEADERS =	${INC_DIR}/execution.h \
			${INC_DIR}/headings.h \
			${INC_DIR}/structures.h \
			${INC_DIR}/signals.h \
			${INC_DIR}/functions.h 

# **************************************************************************** #
# ********************************SRC FILES*********************************** #
# **************************************************************************** #

FILES = main.c \
		${PARS_DIR}/handle_line.c \
		${PARS_DIR}/error_check.c \
		${PARS_DIR}/error_check_redirect.c \
		${PARS_DIR}/error_check_utils.c \
		${PARS_DIR}/error_check_bracket.c \
		${PARS_DIR}/error_unsupported.c \
		${PARS_DIR}/readline_utils.c \
		${PARS_DIR}/ast_parsing.c \
		${PARS_DIR}/ast_maker.c \
		${PARS_DIR}/ast_separator.c \
		${PARS_DIR}/ast_parenthesis.c \
		${PARS_DIR}/cmd_line.c \
		${PARS_DIR}/cmd_files_get.c \
		${PARS_DIR}/cmd_files_add.c \
		${PARS_DIR}/cmd_files_quotes.c \
		${PARS_DIR}/cmd_elements.c \
		${PARS_DIR}/cmd_elements_split.c \
		${PARS_DIR}/cmd_expansions.c \
		${PARS_DIR}/cmd_exp_tild.c \
		${PARS_DIR}/cmd_exp_score.c \
		${PARS_DIR}/cmd_exp_trim.c \
		${PARS_DIR}/cmd_exp_replace.c \
		${PARS_DIR}/cmd_exp_utils.c \
		${PARS_DIR}/cmd_spec_expansions.c \
		${PARS_DIR}/cmd_mergequotes.c \
		${PARS_DIR}/clean.c \
		${EXEC_DIR}/free_tree.c \
		${EXEC_DIR}/execution.c \
		${EXEC_DIR}/exec_utils.c \
		${EXEC_DIR}/cmd_check.c \
		${EXEC_DIR}/exec_paths_absolute.c \
		${EXEC_DIR}/exec_paths_relative.c \
		${EXEC_DIR}/pipes_exec_cmd.c \
		${EXEC_DIR}/exec_paths.c \
		${EXEC_DIR}/cmd_combine.c \
		${EXEC_DIR}/multi_pipe.c \
		${EXEC_DIR}/pipes_childs.c \
		${EXEC_DIR}/pipes_parent.c \
		${EXEC_DIR}/pipes_init.c \
		${EXEC_DIR}/pipes_utils.c \
		${EXEC_DIR}/single_cmd.c \
		${EXEC_DIR}/single_cmd_process.c \
		${EXEC_DIR}/single_cmd_utils.c \
		${EXEC_DIR}/set_io.c \
		${EXEC_DIR}/pipes_cmd_lst.c \
		${REDIRECT_DIR}/redirect.c \
		${REDIRECT_DIR}/redirect_utils.c \
		${EXEC_DIR}/error_msg.c \
		${EXEC_DIR}/error_path_msg.c \
		${REDIRECT_DIR}/heredoc.c \
		${REDIRECT_DIR}/heredoc_traverse.c \
		${REDIRECT_DIR}/heredoc_tmp_files.c \
		${REDIRECT_DIR}/heredoc_utils.c \
		${REDIRECT_DIR}/get_fd.c \
		${REDIRECT_DIR}/set_io_pipes.c \
		${BUILTIN_DIR}/builtin_utils.c \
		${BUILTIN_DIR}/ft_echo.c \
		${BUILTIN_DIR}/ft_pwd.c \
		${BUILTIN_DIR}/ft_cd.c \
		${BUILTIN_DIR}/ft_env.c \
		${BUILTIN_DIR}/ft_export.c \
		${BUILTIN_DIR}/ft_exit.c \
		${BUILTIN_DIR}/ft_export_utils.c \
		${BUILTIN_DIR}/ft_export_no_args.c \
		${BUILTIN_DIR}/ft_export_valid_key.c \
		${BUILTIN_DIR}/ft_export_modify_lst.c \
		${BUILTIN_DIR}/ft_unset.c \
		${ENV_DIR}/env_init.c \
		${ENV_DIR}/env_utils.c \
		${ENV_DIR}/env_convert.c \
		${ENV_DIR}/env_node.c \
		${SIG_DIR}/signals.c \
		${SIG_DIR}/signals_heredoc.c 


OBJ = $(patsubst %.c,build/%.o,$(notdir $(FILES)))


# **************************************************************************** #
# **********************************MAKE************************************** #
# **************************************************************************** #


all:$(LIBFT) $(NAME) 

$(LIBFT): $(shell find $(LIB_DIR) -type f -name "*.c") \
	$(shell find $(LIB_DIR) -type f -name "*.h") \
	$(LIB_DIR)/Makefile

	$(MAKE) -C $(LIB_DIR) --no-print-directory

$(NAME): $(OBJ) $(HEADERS) Makefile $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
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