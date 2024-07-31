# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akloster <akloster@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 17:39:13 by akloster          #+#    #+#              #
#    Updated: 2024/07/30 22:28:46 by akloster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM				=	rm -rf

SRC				=	main.c lexer.c error_handler.c execution.c executor.c \
					free_functions.c get_exec_info.c file_handler.c

LIBft			=	libft/libft.a

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC				=	cc

CFLAGS			=	#-Wall -Wextra -Werror

NAME			=	minishell

$(NAME):		$(OBJ_DIR) $(OBJ) #-g -fsanitize=address
				make -C./libft
				$(CC) $(CFLAGS) $(OBJ) $(LIBft) -lreadline -o $@   

all:			$(NAME)

$(OBJ_DIR)%.o:	%.c
				$(CC) $(CFLAGS) -c $< -o $@

%.o: 			%.c
				$(CC) $(CFLAGS) $< -o $@


$(OBJ_DIR):	
				@mkdir -p $(OBJ_DIR)

clean:
				make clean -C./libft
				$(RM) $(OBJ_DIR)

fclean:			clean
				make fclean -C./libft
				$(RM) $(OBJ) $(NAME) $(OBJ_DIR)

re:				fclean $(NAME)


.PHONY:			all clean fclean re