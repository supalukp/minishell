# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spunyapr <spunyapr@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/11 15:28:49 by rose              #+#    #+#              #
#    Updated: 2025/02/26 15:06:10 by spunyapr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs
INCLUDES = -I. 

# Directories
SRC_DIRS = char list mem print printf string get_next_line
OBJ_DIR = obj

# Source files
SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

# Object files
OBJS = $(SRCS:.c=.o)

# Header files
HEADER_LIBFT = libft.h
HEADER_PRINTF = printf/ft_printf.h
HEADER_GET_NEXT_LINE = get_next_line/get_next_line.h

# Library name
LIBFT = libft.a

all: $(LIBFT)

$(LIBFT): $(OBJS)
	$(AR) $(LIBFT) $(OBJS)

%.o: %.c $(HEADER_LIBFT) $(HEADER_PRINTF) $(HEADER_GET_NEXT_LINE) Makefile
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
      
fclean: clean
	rm -f $(LIBFT)
	
re: fclean all

.PHONY: all clean fclean re