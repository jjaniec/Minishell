/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:53:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/05 19:15:47 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MINISHELL_H__
# define __MINISHELL_H__

# include <ft_printf.h>

# define PRINTF				printf

# define IFS				"\x20\x09\x0a\x00"

typedef struct				s_msh_command
{
	char					*prog_name;
	struct s_prog_param		*prog_prm;
	struct s_msh_command	*next;
}							t_msh_command;

typedef struct				s_prog_param
{
	char					*prm;
	struct s_prog_param		*next;
}							t_prog_param;

typedef struct				s_msh_params
{
	t_msh_command			*input;
	int						input_r;
	char					*cwd;
}							t_msh_params;

extern t_msh_params			*g_msh_params;

t_msh_command				*ft_parse_input(void);

t_msh_params				*ft_create_msh_params_struct(void);

t_prog_param				*ft_create_prog_param_elem(void);

void						ft_print_prompt(void);

void						ft_debug_g_msh_params(void);

void						ft_debug_msh_prog_params(void);

#endif
