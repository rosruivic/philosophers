# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/27 10:18:14 by roruiz-v          #+#    #+#              #
#    Updated: 2023/09/14 20:50:19 by roruiz-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRC		=	philo.c \
			000_error_msg.c \
			100_check_data.c \
			110_init_data.c \
			115_dominant_hand.c \
			200_ctrl_thr.c \
			210_control_routine.c \
			220_ctrl_routine_extras.c \
			300_phi_routine.c \
			310_phi_sleeps_or_thinks.c \
			320_phi_gets_forks.c \
			330_phi_eats.c \
			900_utils.c \
			910_ft_philo_atoi.c

OBJS	= $(SRC:.c=.o)
OFILES = $(addprefix obj/, $(OBJS))

#NAMEB	=	philo_bonus

#SRCB		=	philo_bonus.c

#OBJSB	= $(SRCB:.c=.o)

#OFILESB = $(addprefix objb/, $(OBJSB))

CC		= gcc

FLAGS	= -pthread -Wall -Werror -Wextra -fsanitize=thread -g #-fsanitize=address

#LEAKS = memory-leaks/memory_leaks.a

all:	$(NAME)

bonus:	$(NAMEB)

#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(NAME): $(OFILES)
		$(CC) $(FLAGS) $(EXTRA) $(OFILES) -o $(NAME)
		clear
 		
#$(NAMEB): $(OFILESB)
#		$(CC) $(FLAGS) $(EXTRA) $(OFILESB) -o $(NAMEB)
#		clear
		
$(OFILES): $(SRC)
		@mkdir -p obj/
		gcc -Wall -Wextra -Werror -c $(SRC)
		@mv *.o obj/

#$(OFILESB): $(SRCB)
#		@mkdir -p objb/
#		gcc -Wall -Wextra -Werror -c $(SRCB)
#		@mv *.o objb/

# If a debug with lldb is needed, do 'make' with this rule:
debug: $(LIBFT_PATH) $(MLX42_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(SRC) -o $(NAME) -g
		clear

clean:
		rm -rf obj objb
#		make -C libft clean

fclean: clean
		@rm $(NAME)
#		@rm $(NAME) $(NAMEB)

re:	fclean all
#re:	fclean all bonus

.PHONY: all clean fclean re bonus
