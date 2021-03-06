/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:53:50 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/27 18:48:23 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <ft_printf.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>

# define PRINTF				ft_printf

# define IFS				"\x20\x09\x0a\x00"

typedef struct				s_msh_command
{
	char					*prog_name;
	struct stat				*prog_stats;
	int						stats_rcode;
	pid_t					pid;
	char					**prog_prms;
	int						prog_prms_count;
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
	char					**cur_environ;
	char					*path[255];
	int						input_r;
	char					*cwd_fmt;
	char					*cwd_env;
	char					*home_fmt;
	char					*prev_location;
	char					*user;
}							t_msh_params;

typedef struct				s_process
{
	pid_t					pid;
}							t_process;

extern t_process			*g_cur_process;

extern t_msh_params			*g_msh_params;

t_msh_command				*ft_parse_input(void);

t_msh_params				*ft_create_msh_params_struct(char **environ);

t_prog_param				*ft_create_prog_param_elem(void);

void						ft_print_prompt(t_msh_params *msh_params);

void						ft_debug_msh_params(t_msh_params *msh_params);

int							ft_is_ifs(char c);

char						**ft_parse_prog_params(char *s, \
								t_msh_command *input);

char						*ft_parse_prog_param_nb(char *str, int nb);

void						ft_store_env_variables_fmt(\
								t_msh_params *msh_params);

char						*ft_strjoin_path(char *s1, char *s2);

void						ft_start_prog(t_msh_params *msh_params);

int							ft_wait_pid(pid_t pid);

int							ft_can_exec_path(t_msh_command *cmd, char *path);

void						ft_err_cmd_not_found(t_msh_command *cmd);

void						ft_handle_err_code(int err, char *prog_name);

int							ft_handle_err(t_msh_command *cmd);

int							ft_is_builtin(t_msh_params *msh_params, \
								t_msh_command *cmd);

void						ft_exec_builtin(int blt, t_msh_params *msh_params, \
								t_msh_command *cmd);

char						**ft_add_ptr_to_tab(char **tab, char *e);

char						*ft_update_path_value(char **path, \
								char *var_name, char *data);

void						ft_exec_builtin_echo(t_msh_params *msh_params, \
								t_msh_command *cmd);

void						ft_exec_builtin_cd(t_msh_params *msh_params, \
								t_msh_command *cmd);

char						**ft_msh_setenv(t_msh_params *msh_params, \
								char **env, char *name, char *value);

void						ft_msh_unsetenv(t_msh_params *msh_params, \
								char *name);

char						*ft_get_path_var_val(char **env, char *var);

void						ft_refresh_fmt_ptrs(t_msh_params *msh_params);

void						ft_free_msh_command(t_msh_command *mc);

void						ft_free_msh_params(t_msh_params *mp);

void						ft_free_ptr_tab(void **ptr);

t_msh_command				*ft_create_msh_command(void);

void						ft_handle_child_sigint(void);

void						ft_sigint_handler(int signo);

void						ft_fork_and_start(char *prog_path, \
								char **prog_params, char **prog_env, \
								int exit_on_failure);

#endif
