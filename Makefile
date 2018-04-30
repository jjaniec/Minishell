# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/05 21:53:56 by jjaniec           #+#    #+#              #
#    Updated: 2018/04/30 13:29:51 by jjaniec          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

UNAME_S := $(shell uname -s)

SRC_NAME = 	ft_add_ptr_to_tab.c \
			ft_can_exec_path.c \
			ft_create_msh_struct.c \
			ft_debug_msh_struct.c \
			ft_exec_builtin.c \
			ft_exec_builtin_cd.c \
			ft_exec_builtin_echo.c \
			ft_fork_and_start.c \
			ft_free_msh_struct.c \
			ft_get_path_var_val.c \
			ft_handle_err.c \
			ft_handle_sig.c \
			ft_is_builtin.c \
			ft_msh_setenv.c \
			ft_msh_unsetenv.c \
			ft_parse_input.c \
			ft_parse_prog_param_nb.c \
			ft_parse_prog_params.c \
			ft_print_prompt.c \
			ft_start_prog.c \
			ft_store_env_variables_fmt.c \
			ft_strjoin_path.c \
			ft_update_path_value.c \
			ft_wait_pid.c \
			main.c

SRC_DIR = ./srcs/
INCLUDES_DIR = ./includes/
OBJ_DIR = ./objs/
FT_PRINTF_DIR = ./ft_printf

SRC = $(addprefix $(SRC_DIR), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_DIR), $(SRC_NAME:.c=.o))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
#DEV_FLAGS = -fsanitize=address -fno-omit-frame-pointer
IFLAGS = -I$(FT_PRINTF_DIR)/includes -I./$(INCLUDES_DIR)
LFLAGS = -L$(FT_PRINTF_DIR) -lftprintf

CFLAGS += $(DEV_FLAGS)
LIBFTPRINTF = $(addprefix $(FT_PRINTF_DIR),"/libftprintf.a")

MAKEFILE_STATUS = $(addprefix $(addprefix $(FT_PRINTF_DIR),"/libft"),"/.makefile_status")

UNAME_S := $(shell uname -s)

define ui_line
	$(MAKEFILE_STATUS) $(1) $(2) || true
endef

all : $(NAME)

$(NAME) : $(LIBFTPRINTF) $(OBJ)
ifeq ($(UNAME_S),Linux)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) $(LIBFTPRINTF) -o $(NAME)
endif
ifeq ($(UNAME_S),Darwin)
	@$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $(NAME)
endif

$(OBJ_DIR)%.o : $(SRC_DIR)%.c ./includes/minishell.h
	@mkdir -p $(OBJ_DIR)
	@gcc $(CFLAGS) -c $(IFLAGS) $< -o $@ && $(call ui_line, $@, $(NAME))

$(FT_PRINTF_DIR):
	git clone https://github.com/jjaniec/ft_printf $(FT_PRINTF_DIR) 2> /dev/null || true

$(LIBFTPRINTF): $(FT_PRINTF_DIR)
	make -C $(FT_PRINTF_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@make clean -C $(FT_PRINTF_DIR)

fclean: clean
	@make fclean -C $(FT_PRINTF_DIR)
	@rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re
