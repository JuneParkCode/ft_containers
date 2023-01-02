# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sungjpar <sungjpar@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/10 00:54:23 by sungjpar          #+#    #+#              #
#    Updated: 2022/12/28 12:48:36 by sungjpar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = c++

CFLAGS = -Wall -Wextra -Werror -std=c++98  -pedantic 

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
endif

NAME = Fixed 

INC_DIR = ./include/

SRC_DIR = ./src/

INC_FLAG = -I$(INC_DIR)

SRC_FILES = $(addprefix $(SRC_DIR),\
						source/vector/vector.cpp\
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
