# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 00:54:23 by sungjpar          #+#    #+#              #
#    Updated: 2023/01/04 16:34:54 by sungjpar         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98  -pedantic 

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
endif

NAME = container

INC_DIR = ./include/

SRC_DIR = ./source/

INC_FLAG = -I$(INC_DIR)

SRC_FILES = $(addprefix $(SRC_DIR),\
			test.cpp\
			)

OBJ = ${SRC_FILES:.cpp=.o}

all 	: $(NAME)

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(INC_FLAG)

%.o 	: %.cpp
	$(CC) $(CFLAGS) $(INC_FLAG) -c $< -o $@

clean	:
	rm -f $(OBJ)

fclean	:
	rm -f $(NAME)
	$(MAKE) clean

re		:
	$(MAKE) fclean
	$(MAKE) all

.PHONY	: clean fclean re all
