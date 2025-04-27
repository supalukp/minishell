# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syukna <syukna@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/13 13:56:00 by syukna            #+#    #+#              #
#    Updated: 2025/02/21 13:09:42 by syukna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc
CFLAGS = -Wall -Werror -Wextra
FUNCTIONS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_strlen.c ft_toupper.c ft_tolower.c \
			ft_strchr.c ft_strrchr.c ft_strncmp.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_strlcpy.c ft_strlcat.c \
			ft_memcpy.c ft_strnstr.c ft_memmove.c ft_memcmp.c \
			ft_memchr.c ft_strdup.c ft_substr.c ft_calloc.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
			ft_strmapi.c ft_striteri.c 
PRINTF =	ft_printf/ft_printf.c ft_printf/ft_print_uns.c \
			ft_printf/ft_print_hex.c ft_printf/ft_print_p.c \
			ft_printf/ft_char_to_hex.c ft_printf/ft_putchar_fd.c \
			ft_printf/ft_putstr_fd.c ft_printf/ft_putendl_fd.c \
			ft_printf/ft_putnbr_fd.c
LINKLIST =  linked_list/ft_lstnew.c linked_list/ft_lstadd_front.c linked_list/ft_lstsize.c \
			linked_list/ft_lstlast.c linked_list/ft_lstadd_back.c linked_list/ft_lstdelone.c \
			linked_list/ft_lstclear.c linked_list/ft_lstiter.c linked_list/ft_lstmap.c
GETNEXTLINE = get_next_line/get_next_line.c
CONVERSIONS = ${FUNCTIONS:.c=.o} ${LINKLIST:.c=.o} ${PRINTF:.c=.o} ${GETNEXTLINE:.c=.o}
HEADERS = libft.h ft_printf/ft_printf.h get_next_line/get_next_line.h

all: $(NAME)

$(NAME): $(CONVERSIONS) $(HEADERS)
	@ar rcs $(NAME) $(CONVERSIONS)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f ${CONVERSIONS} .bonus

fclean: clean
	@rm -f ${NAME} 

re: fclean all

.PHONY: all bonus clean fclean re