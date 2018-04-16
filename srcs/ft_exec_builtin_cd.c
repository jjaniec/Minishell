/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 22:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 21:47:54 by jjaniec          ###   ########.fr       */
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
** Call chdir to new path
*/

static void	ft_change_dir(char *path)
{
	struct stat	path_stats;

	if (!path && g_msh_params->home_fmt)
		ft_change_dir(g_msh_params->home_fmt);
	if (path && chdir(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		if (stat(path, &path_stats))
			ft_putstr_fd(": no such file or directory\n", 2);
		else
			ft_putstr_fd(": permission denied\n", 2);
	}
}

/*
** Inspect cd argument to know if passed argument is a relative/absolute path
** or if argument is '-', then refresh last previous location
*/

static void	ft_cd_relative_dir(t_msh_command *cmd)
{
	char	*new_dir_path;
	char	cwd_fmt[1024];

	if ((getcwd(cwd_fmt, sizeof(cwd_fmt))))
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
	free(g_msh_params->prev_location);
	g_msh_params->prev_location = (g_msh_params->cwd_fmt) ? \
		(ft_strdup(g_msh_params->cwd_fmt)) : NULL;
	ft_update_path_value(g_msh_params->cur_environ, "OLDPWD", \
		g_msh_params->prev_location);
	ft_refresh_cwd_env();
}
