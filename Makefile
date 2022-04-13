# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/13 14:02:33 by amarchan          #+#    #+#              #
#    Updated: 2022/04/13 17:51:50 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/04 09:22:13 by amarchan          #+#    #+#              #
#    Updated: 2022/04/12 18:53:28 by amarchan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

NAME_LIBFT = libft.a

NAME_MLX = libmlx.a

NORMINETTE_BIN = norminette
NM_BIN = nm

DIR_MLX = minilibx-linux/

DIR_LIBFT = libft/

SRCS =	src/so_long.c \
		parsing/parsing.c \
		get_next_line/get_next_line.c \
		get_next_line/get_next_line_utils.c \

OBJS := ${SRCS:.c=.o}

CC = gcc

CFLAGS = -g3
CFLAGS_MLX = -lXext -lX11

AR = ar rcs

RM = rm -rf

INC_DIR = headers
INC_LIBFT = libft

.c.o: $(SRCS)
	$(CC) $(CFLAGS) -c -I ${INC_DIR} -I ${INC_LIBFT} $< -o ${<:.c=.o}

all: $(NAME_LIBFT) $(NAME_MLX) $(NAME) 

$(NAME_LIBFT):
	make -C $(DIR_LIBFT)
	cp $(DIR_LIBFT)libft.a .

$(NAME_MLX):
	make -C $(DIR_MLX)
	cp $(DIR_MLX)libmlx.a .

$(NAME): ${OBJS}
	gcc $(CFLAGS) -o $(NAME) $(OBJS) $(NAME_LIBFT) $(NAME_MLX) $(CFLAGS_MLX)

clean:
	${RM} ${OBJS}
	make -C $(DIR_LIBFT) clean
	make -C $(DIR_MLX) clean

fclean: clean
	${RM} ${NAME} ${NAME_LIBFT} ${NAME_MLX}
	make -C $(DIR_LIBFT) fclean
	${RM} $(DIR_MLX)libmlx.a
	${RM} $(DIR_MLX)libmlx_Linux.a
	

re: fclean all

norme:
	${NORMINETTE_BIN} ${SRCS}

sym:
	${NM_BIN} -Dgu $(NAME)

.PHONY: all clean fclean re norme sym