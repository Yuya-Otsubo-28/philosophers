# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yotsubo <yotsubo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/30 10:05:26 by yotsubo           #+#    #+#              #
#    Updated: 2022/12/14 15:47:04 by yotsubo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = 	src/main.c\
		src/error.c\
		src/init.c\
		src/philo_utils.c\
		src/make_philos.c\
		src/monitor.c\
		src/philo_event.c\
		src/message.c
OBJDIR = ./obj
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
INCLUDE = -I ./include
CC	= cc
CFLAGS = -Wall -Wextra -Werror ##-fsanitize=thread

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

$(OBJDIR)/%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

clean :
	$(RM) $(OBJS)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re
