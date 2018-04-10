/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_prog.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:01:56 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 16:33:29 by jjaniec          ###   ########.fr       */
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
		return (NULL);
	}
	return (s);
}

/*
** Check if command is a path to an executable and tries to
** execute it
*/

static void		ft_is_prog_name_path(t_msh_command *cmd)
{
	char	*path;

	cmd->prog_stats = malloc(sizeof(struct stat));
	path = ((cmd->prog_name[0] == '.') ? \
		(ft_strjoin_path(g_msh_params->cwd, cmd->prog_name)) : \
		(cmd->prog_name));
	cmd->stats_rcode = stat(path, cmd->prog_stats);
	if (cmd->stats_rcode >= 0 && !ft_handle_err(cmd))
	{
		if (0 == (g_msh_params->input->pid = fork()))
			execve(path, g_msh_params->input->prog_prms, environ);
		ft_wait_pid(g_msh_params->input->pid);
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

void			ft_start_prog_path(void)
{
	int		i;
	char	*prog_path;

	i = -1;
	prog_path = NULL;
	while (g_msh_params->path[++i])
	{
		if ((prog_path = \
			ft_is_path_valid(g_msh_params->path[i], g_msh_params->input)))
		{
			if (ft_can_exec_path(g_msh_params->input, prog_path))
				break ;
			else
			{
				if (0 == (g_msh_params->input->pid = fork()) && -1 == \
					execve(prog_path, g_msh_params->input->prog_prms, environ))
					break ;
				ft_wait_pid(g_msh_params->input->pid);
				free(prog_path);
				break ;
			}
		}
	}
	if (!prog_path)
		ft_err_cmd_not_found(g_msh_params->input);
}

/*
** Determine if passed program name is a path or not and
** pass it to the adapted function
*/

void			ft_start_prog(void)
{
	if (g_msh_params->input->prog_name[0] == '/' || \
		g_msh_params->input->prog_name[0] == '.')
		ft_is_prog_name_path(g_msh_params->input);
	else
		ft_start_prog_path();
}
