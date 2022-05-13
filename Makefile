# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mandriic <mandriic@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 18:07:49 by mandriic          #+#    #+#              #
#    Updated: 2022/04/23 18:07:54 by mandriic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES_DIR		= 	./src
SOURCES_FILES	=	philo.c\
					ft_atoi.c\
					parsing.c\
					add_func.c\
					func_philo.c\
					create_list_pth.c\
					forks.c

SRC_DIR_BONUS	= 	./src_bonus
SRC_FILES_BONUS	=	ft_atoi.c\
					philo.c\
					add_func.c\
					sem_forks.c

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))
SOURCES_BONUS	=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJECTS			= 	$(SOURCES:.c=.o)
OBJECTS_BONUS	= 	$(SOURCES_BONUS:.c=.o)

NAME			=	philo
NAME_BONUS		=	philo_bonus

CC				=	gcc -pthread -Wall -Wextra -Werror -g
RM				=	rm -f

# CFLAGS			=	-Wall -Wextra -Werror  -fsanitize=thread

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)
bonus:			$(NAME_BONUS)

$(NAME):		$(OBJECTS) ./src/philo.h
				$(CC) $(CFLAGS) $(OBJECTS)  -o $(NAME)

$(NAME_BONUS):	$(OBJECTS_BONUS) ./src/philo.h
				$(CC) $(CFLAGS) $(OBJECTS_BONUS)  -o $(NAME_BONUS)

clean:
				$(RM) $(OBJECTS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

clean_bonus:
				$(RM) $(OBJECTS_BONUS)

fclean_bonus:	clean_bonus
				$(RM) $(NAME_BONUS)

re_bonus:		fclean_bonus bonus

.PHONY:		all bonus clean fclean re clean_bonus fclean_bonus re_bonus
