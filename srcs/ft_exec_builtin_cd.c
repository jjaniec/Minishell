/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 22:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 15:43:07 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Refresh current path with getcwd
*/

static void	ft_refresh_cwd_env(void)
{
	char	cwd_new_fmt[1024];

	if (getcwd(cwd_new_fmt, sizeof(cwd_new_fmt)) == NULL)
		ft_putstr_fd("minishell: .: permission denied\n", 2);
	else
	{
		g_msh_params->cwd_env = \
			ft_update_path_value(g_msh_params->cur_environ, "PWD", cwd_new_fmt);
		if (g_msh_params->cwd_env && ft_strlen(g_msh_params->cwd_env) >= 4)
			g_msh_params->cwd_fmt = &(g_msh_params->cwd_env[4]);
		else
			g_msh_params->cwd_fmt = NULL;
	}
}

/*
** Call chdir to new path & refresh g_msh_params->prev_location
*/

static void	ft_print_cd_err(char *path, struct stat *path_stats)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (stat(path, path_stats))
		ft_putstr_fd(": no such file or directory\n", 2);
	else if (!S_ISDIR(path_stats->st_mode))
		ft_putstr_fd(": not a directory\n", 2);
	else
		ft_putstr_fd(": permission denied\n", 2);
}

static void	ft_change_dir(char *path)
{
	struct stat	path_stats;
	char		*cwd_path;
	char		*new_prev_location;

	cwd_path = malloc(sizeof(char) * 1024);
	new_prev_location = getcwd(cwd_path, 1024);
	if (!path && g_msh_params->home_fmt)
		ft_change_dir(g_msh_params->home_fmt);
	if (path && !chdir(path) && new_prev_location)
	{
		free(g_msh_params->prev_location);
		g_msh_params->prev_location = new_prev_location;
		ft_update_path_value(g_msh_params->cur_environ, "OLDPWD", \
			g_msh_params->prev_location);
	}
	else if (path && chdir(path))
	{
		free(cwd_path);
		ft_print_cd_err(path, &path_stats);
	}
	else
		free(cwd_path);
}

/*
** Inspect cd argument to know if passed argument is a relative/absolute path
** or if argument is '-', then refresh last previous location
*/

static void	ft_cd_relative_dir(t_msh_command *cmd)
{
	char	*new_dir_path;
	char	cwd_fmt[1024];

	if (getcwd(cwd_fmt, sizeof(cwd_fmt)))
	{
		new_dir_path = ft_strjoin_path(cwd_fmt, cmd->prog_prms[1]);
		ft_change_dir(new_dir_path);
		free(new_dir_path);
	}
}

void		ft_exec_builtin_cd(t_msh_command *cmd)
{
	if (!(cmd->prog_prms[0] && cmd->prog_prms[1]))
		ft_change_dir(g_msh_params->home_fmt);
	else if (cmd->prog_prms[1][0] == '/')
		ft_change_dir(cmd->prog_prms[1]);
	else if (ft_strcmp(cmd->prog_prms[1], "-") == 0)
		ft_change_dir(g_msh_params->prev_location);
	else if (cmd->prog_prms[1])
		ft_cd_relative_dir(cmd);
	ft_refresh_cwd_env();
}
