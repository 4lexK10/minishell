# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akiener <akiener@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/04 17:39:13 by akloster          #+#    #+#              #
#    Updated: 2024/10/24 14:55:03 by akiener          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RM				=	rm -rf

SRC_DIR			=	src/

SRC				=	main.c exec/utils/error_handler.c					\
					exec/piper.c exec/initializer.c builtins/ft_echo.c	\
					exec/redir_handler.c exec/executioner.c				\
					exec/utils/free_functions.c exec/process_handler.c	\
					exec/utils/wrapper_fcts.c exec/utils/exec_tools.c	\
					builtins/ft_cd.c exec/utils/built_tools.c			\
					builtins/ft_exit.c builtins/ft_pwd.c 				\
					builtins/ft_env.c builtins/ft_export.c				\
					exec/utils/env_tools.c builtins/ft_unset.c			\
					exec/utils/tools.c	exec/here_doc_handler.c			\
					exec/utils/process_tools.c										\
					parsing/check_envp.c								\
					parsing/parsing.c parsing/error.c					\
					parsing/lexer_tok.c parsing/list_data.c				\
					parsing/pars_utils.c parsing/split_input.c			\
					parsing/env_utils.c parsing/check_our_env.c

HEADERS			=	includes/minishell.h

LIBft			=	libft/libft.a

OBJ_DIR			=	objs/

OBJ				=	$(addprefix $(OBJ_DIR), $(SRC:.c=.o))

CC				=	cc

CFLAGS			=	-Iincludes -Wall -Wextra -Werror

NAME			=	minishell

$(NAME):		$(OBJ_DIR) $(OBJ) 
				make -C./libft
				$(CC) $(CFLAGS) $(OBJ) $(LIBft) -lreadline -L /Users/$(shell whoami)/homebrew/Cellar/readline/8.2.13/lib 	\
				-I /Users/$(shell whoami)/homebrew/Cellar/readline/8.2.13/include -o $@

all:			$(NAME)

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c $(HEADERS)
				@mkdir -p $(dir $@)
				$(CC) $(CFLAGS) -c $< -o $@


$(OBJ_DIR):	
				@mkdir -p $(OBJ_DIR)

clean:
				make clean -C./libft
				$(RM) $(OBJ_DIR)

fclean:			clean
				make fclean -C./libft
				$(RM) $(NAME) $(OBJ_DIR)

re:				fclean $(NAME)


.PHONY:			all clean fclean re