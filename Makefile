SOURCES_DIR		= 	./src
SOURCES_FILES	=	philo.c\
					ft_atoi.c\
					parsing.c\
					add_func.c\
					func_philo.c\
					create_list_pth.c\
					forks.c




# SRC_DIR_BONUS	= 	./bonus
# SRC_FILES_BONUS	=	checker.c\
# 					oper_doble_push_bonus.c\
# 					oper_rot_revrot_bonus.c\
# 					oper_swap_bonus.c\
# 					../get_next_line/get_next_line.c\
# 					../get_next_line/get_next_line_utils.c\
# 					checker_util.c\

SOURCES			=	$(addprefix $(SOURCES_DIR)/, $(SOURCES_FILES))
# SOURCES_BONUS	=	$(addprefix $(SRC_DIR_BONUS)/, $(SRC_FILES_BONUS))

OBJECTS			= 	$(SOURCES:.c=.o)
# OBJECTS_BONUS	= 	$(SOURCES_BONUS:.c=.o)

NAME			=	philo
# NAME_BONUS		=	checker

CC				=	gcc 
RM				=	rm -f

CFLAGS			=	-Wall -Wextra -Werror

.c.o:
				$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all:			$(NAME)
# bonus:			$(NAME_BONUS)

$(NAME):		$(OBJECTS)
				$(CC) $(CFLAGS) $(OBJECTS)  -o $(NAME)

# $(NAME_BONUS):	$(LIBFT) $(FT_PRINTF) $(OBJECTS_BONUS) 
# 				$(CC) $(CFLAGS) $(LIBFT) $(OBJECTS_BONUS)  $(FT_PRINTF)  -o $(NAME_BONUS)

clean:
				$(RM) $(OBJECTS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean all

# clean_bonus:
# 				$(RM) $(OBJECTS_BONUS)

# fclean_bonus:	clean_bonus
# 				$(RM) $(NAME_BONUS)

# re_bonus:		fclean_bonus bonus

.PHONY:		all clean fclean re