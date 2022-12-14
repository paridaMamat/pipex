NAME		= pipex

NAME_B      = pipex_bonus

SRCS		= pipex.c \
			  execute.c\
			  utils/exit_perror.c\
			  utils/free_array.c\
			  utils/ft_split.c\
			  utils/ft_strjoin.c\
			  utils/ft_strlen.c\
			  utils/ft_strncmp.c

SRCS_BONUS  = pipex_bonus.c \
			  execute.c \
			  multiple_pipe.c\
			  utils/exit_perror.c\
			  utils/free_array.c\
			  utils/ft_split.c\
			  utils/ft_strjoin.c\
			  utils/ft_strlen.c\
			  utils/ft_strncmp.c\
			  utils/joint_and_free.c\
			  utils/ft_putstr_fd.c

OBJS		= $(SRCS:%.c=%.o)
OBJS_BONUS  = $(SRCS_BONUS:%.c=%.o)


FLAGS		= -Wall -Wextra -Werror -g3

all			:	$(NAME) 

bonus       :   $(NAME_B)

$(NAME)		:	$(OBJS)
		gcc  $(FLAGS) $(OBJS) -o $(NAME)

$(NAME_B)   :$(OBJS_BONUS)
		gcc  $(FLAGS) $(OBJS_BONUS) -o $(NAME_B)


%.o			:	%.c
		gcc -c $(FLAGS) -I./ $^ -o $@ 


clean		:
		rm -f $(OBJS)
		rm -f $(OBJS_BONUS)

fclean		:	clean
		rm -f $(NAME)
		rm -f $(NAME_B)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
