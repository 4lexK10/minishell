# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akloster <akloster@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 17:39:13 by akloster          #+#    #+#              #
#    Updated: 2024/09/07 18:47:52 by akloster         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM				=	rm -rf

SRC_DIR			=	src/

SRC				=	main.c lexer.c exec/utils/error_handler.c exec/piper.c	 \
					exec/initializer.c exec/executioner.c exec/redir_handler.c	 \
					exec/utils/free_functions.c exec/process_handler.c 		 \
					exec/utils/wrapper_fcts.c parsing/check_envp.c 			 \
					parsing/parsing.c parsing/error.c parsing/env_utils.c	 \
					parsing/lexer_tok.c parsing/list_data.c					 \
					parsing/pars_utils.c parsing/split_input.c

HEADERS			=	includes/minishell.h

LIBft			=	libft/libft.a

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC				=	cc

CFLAGS			=	 -Iincludes #-Wall -Wextra -Werror

NAME			=	minishell

$(NAME):		$(OBJ_DIR) $(OBJ) #-g -fsanitize=address
				make -C./libft
				$(CC) $(CFLAGS) $(OBJ) $(LIBft) -lreadline -g -fsanitize=address -o $@   

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS)
				@mkdir -p $(dir $@)
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