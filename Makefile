# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: majosue <majosue@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/13 10:14:46 by majosue           #+#    #+#              #
#    Updated: 2021/11/18 17:39:08 by majosue          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = server
NAME2 = client
COMPILERC = gcc
FLAGS = -Wall -Wextra -Werror
HEADERS = ./includes/server.h ./libft/includes/libft.h ./libftprintf/includes/ft_printf.h
HEADERS2 = ./includes/client.h ./libft/includes/libft.h
HEADERS_DIRECTORY = ./includes/ ./libft/includes
SOURCES_DIRECTORY = ./sources/
OBJECTS_DIRECTORY = ./objects/
INCLUDES = $(addprefix -I , $(HEADERS_DIRECTORY))
SOURCES = server.c server_utils.c
SOURCES2 = client.c
OBJECTS = $(SOURCES:.c=.o)
OBJECTS := $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS))
SOURCES := $(addprefix $(SOURCES_DIRECTORY), $(SOURCES))
OBJECTS2 = $(SOURCES2:.c=.o)
OBJECTS2 := $(addprefix $(OBJECTS_DIRECTORY), $(OBJECTS2))
SOURCES2 := $(addprefix $(SOURCES_DIRECTORY), $(SOURCES2))

.PHONY: libft libftprintf clean fclean re

all: $(NAME) $(NAME2)

libft:
	@$(MAKE) -C libft

libftprintf:
	@$(MAKE) -C libftprintf

$(NAME):: libft libftprintf

$(NAME):: $(OBJECTS_DIRECTORY) $(OBJECTS)
	$(COMPILERC) -o $(NAME) $(OBJECTS) $(INCLUDES) -L libft/ -lft -L libftprintf/ -lftprintf

$(NAME2):: libft

$(NAME2):: $(OBJECTS_DIRECTORY) $(OBJECTS2)
	$(COMPILERC) -o $(NAME2) $(OBJECTS2) $(INCLUDES) -L libft/ -lft

$(OBJECTS): $(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS)
	$(COMPILERC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OBJECTS2): $(OBJECTS_DIRECTORY)%.o : $(SOURCES_DIRECTORY)%.c $(HEADERS2)
	$(COMPILERC) $(FLAGS) $(INCLUDES) -o $@ -c $<

$(OBJECTS_DIRECTORY):
	@mkdir -p $(OBJECTS_DIRECTORY)

clean:
	@rm -rf $(OBJECTS_DIRECTORY)
	@make -C libft/ clean
	@make -C libftprintf/ clean

fclean: clean
	@rm -f $(NAME) $(NAME2)
	@make -C libft/ fclean
	@make -C libftprintf/ fclean

re: fclean all
