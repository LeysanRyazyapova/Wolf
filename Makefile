
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 15:24:07 by tmiranda          #+#    #+#              #
#    Updated: 2020/11/24 18:03:24 by tmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	$(addprefix src/, \
			main.c \
			cast_ray.c \
			check_map.c \
			check_utils.c \
			draw.c \
			get_ceil_floor_color.c \
			initialisation.c \
			keyboard.c \
			make_bmp.c \
			parse_map.c \
			parse_player_sprites.c \
			parsetostruct.c \
			rotate.c \
			resolution.c \
			sprites.c \
			valid_massive.c \
			walking.c) \
			get_next_line/get_next_line.c 

SRC_DIR	= src/
OBJ_DIR	= bin/
HEADER	= src/cub3d.h
LIB_HEADER	= Libft/libft.h
LIBFT_DIR	= Libft/
LIBFT	= libft.a
LIB_SRCS	= ft_memset.c				\
			ft_bzero.c					\
			ft_memcpy.c					\
			ft_memccpy.c				\
			ft_memchr.c					\
			ft_memmove.c				\
			ft_memcmp.c					\
			ft_strlen.c					\
			ft_strlcpy.c				\
			ft_strlcat.c				\
			ft_strnstr.c				\
			ft_atoi.c					\
			ft_isalpha.c				\
			ft_isdigit.c				\
			ft_isalnum.c				\
			ft_isascii.c				\
			ft_isprint.c				\
			ft_toupper.c				\
			ft_tolower.c				\
			ft_strncmp.c				\
			ft_strrchr.c				\
			ft_strchr.c					\
			ft_calloc.c					\
			ft_strdup.c					\
			ft_substr.c					\
			ft_strjoin.c				\
			ft_strtrim.c				\
			ft_putchar_fd.c				\
			ft_putstr_fd.c				\
			ft_putendl_fd.c				\
			ft_putnbr_fd.c				\
			ft_strmapi.c				\
			ft_itoa.c					\
			ft_split.c					\
			ft_free_matrix.c			\
			ft_get_next_line.c			\
			ft_get_next_line_utils.c	\
			ft_lstnew.c					\
			ft_lstadd_front.c			\
			ft_lstsize.c				\
			ft_lstlast.c				\
			ft_lstadd_back.c			\
			ft_lstdelone.c				\
			ft_lstclear.c				\
			ft_lstmap.c					\
			ft_lstiter.c

OBJS		=	${SRCS:.c=.o}

LIB_OBJS	=	${LIB_SRCS:.c=.o}
NAME		=	cub3D

CC			=	gcc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror -MMD


MLXFLAGS	=	-lmlx -framework OpenGL -framework AppKit

%.o:	%.c
	$(CC) $(CFLAGS) -Iget_next_line/ -ILibft -Imlx -c $< -o ${<:.c=.o} -g

.PHONY: all
all:		${NAME}	

$(NAME):	${OBJS} ${HEADER} ${LIB_HEADER} 
		${MAKE} -C mlx
		${MAKE} -C libft
		${CC} ${CFLAGS} -Iget_next_line/ -ILibft -Imlx ${OBJS} libft/libft.a -Lmlx ${MLXFLAGS} -o ${NAME} 

${LIBFT_DIR}${LIBFT}:	${LIB_OBJS}
						${MAKE} -C ${LIBFT_DIR}

${LIB_OBJS}:			Libft/libft.h


.PHONY: clean
clean:	
			${RM} ${OBJS}
			${RM} $(OBJS:.o=.d)
			${MAKE} clean -C Libft
			${MAKE} clean -C mlx
.PHONY: fclean
fclean:		clean
			${RM} ${NAME}
			${MAKE} fclean -C Libft
			${RM} libmlx.a
			${RM} screen.bmp

.PHONY: re
re:			fclean all
-include	$(OBJS:.o=.d)