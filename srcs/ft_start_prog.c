/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_prog.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:01:56 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 22:21:14 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Check if an executable exists with current path entry
*/

static char		*ft_is_path_valid(char *prog_path, t_msh_command *cmd)
{
	char			*s;

	cmd->prog_stats = malloc(sizeof(struct stat));
	s = ft_strjoin_path(prog_path, cmd->prog_name);
	if ((cmd->stats_rcode = stat(s, cmd->prog_stats)) < 0)
	{
		free(s);
		free(cmd->prog_stats);
		cmd->prog_stats = NULL;
		return (NULL);
	}
	return (s);
}

/*
** Check if command is a path to an executable and tries to
** execute it
*/

static void		ft_is_prog_name_rel_path(t_msh_params *msh_params, \
					t_msh_command *cmd)
{
	char	*path;
	char	cur_path_fmt[1024];

	cmd->prog_stats = malloc(sizeof(struct stat));
	if (!(getcwd(cur_path_fmt, sizeof(cur_path_fmt))))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->prog_name, 2);
		ft_putstr_fd(": permission denied\n", 2);
	}
	path = ft_strjoin_path(cur_path_fmt, cmd->prog_name);
	cmd->stats_rcode = stat(path, cmd->prog_stats);
	if (cmd->stats_rcode >= 0 && !ft_handle_err(cmd))
	{
		ft_fork_and_start(path, msh_params->input->prog_prms, \
			msh_params->cur_environ, 1);
	}
	else if (cmd->stats_rcode < 0)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(cmd->prog_name, 2);
		ft_putchar_fd('\n', 2);
	}
	free(path);
}

static void		ft_is_prog_name_abs_path(t_msh_params *msh_params, \
					t_msh_command *cmd)
{
	cmd->prog_stats = malloc(sizeof(struct stat));
	cmd->stats_rcode = stat(cmd->prog_name, cmd->prog_stats);
	if (cmd->stats_rcode >= 0 && !ft_handle_err(cmd))
	{
		ft_fork_and_start(cmd->prog_name, msh_params->input->prog_prms, \
			msh_params->cur_environ, 1);
	}
	else if (cmd->stats_rcode < 0)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putstr_fd(cmd->prog_name, 2);
		ft_putchar_fd('\n', 2);
	}
}

/*
** Cycle through path entries to find executable of passed command
** if an executable is found and is not executable, print error and break,
** if no executable were found with path entries, call ft_err_cmd_not_found
*/

void			ft_start_prog_path(t_msh_params *msh_params)
{
	int		i;
	char	*prog_path;

	i = -1;
	prog_path = NULL;
	while (msh_params->path[++i])
		if ((prog_path = \
			ft_is_path_valid(msh_params->path[i], msh_params->input)))
		{
			if (ft_can_exec_path(msh_params->input, prog_path))
			{
				free(prog_path);
				break ;
			}
			else
			{
				ft_fork_and_start(prog_path, \
					msh_params->input->prog_prms, \
					msh_params->cur_environ, 1);
				free(prog_path);
				break ;
			}
		}
	if (!prog_path)
		ft_err_cmd_not_found(msh_params->input);
}

/*
** Determine if passed program name is a path or not and
** pass it to the adapted function
*/

void			ft_start_prog(t_msh_params *msh_params)
{
	if (msh_params->input->prog_name[0] == '/')
		ft_is_prog_name_abs_path(msh_params, msh_params->input);
	else if (ft_strchr(msh_params->input->prog_name, '/'))
		ft_is_prog_name_rel_path(msh_params, msh_params->input);
	else
		ft_start_prog_path(msh_params);
}
