/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:53:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/09 18:42:42 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ft_printf.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>


# define PRINTF				printf

# define IFS				"\x20\x09\x0a\x00"

typedef struct				s_msh_command
{
	char					*prog_name;
	struct stat				*prog_stats;
	int						stats_rcode;
	pid_t					pid;
	char					**prog_prms;
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
	char					*path[255];
	int						input_r;
	char					*cwd;
	char					*home;
	char					*user;
}							t_msh_params;

extern t_msh_params			*g_msh_params;
extern char 				**environ;

t_msh_command				*ft_parse_input(void);

t_msh_params				*ft_create_msh_params_struct(void);

t_prog_param				*ft_create_prog_param_elem(void);

void						ft_print_prompt(void);

void						ft_debug_g_msh_params(void);

void						ft_debug_msh_prog_params(void);

int							ft_is_ifs(char c);

char						**ft_parse_prog_params(char *s, t_msh_command *input);

char						*ft_parse_prog_param_nb(char *str, int nb);

void						ft_store_env_variables(void);

char						*ft_strjoin_path(char *s1, char *s2);

void						ft_start_prog(void);

unsigned int				ft_wait_pid(pid_t pid);

int							ft_can_exec_path(t_msh_command *cmd, char *path);


#endif
