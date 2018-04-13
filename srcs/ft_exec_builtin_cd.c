/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin_cd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 22:44:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/13 19:09:01 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**
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

static void	ft_change_dir(char *path)
{
	struct stat	path_stats;

	if (!path && g_msh_params->home_fmt)
		ft_change_dir(g_msh_params->home_fmt);
	if (chdir(path))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		if (stat(path, &path_stats))
			ft_putstr_fd(": no such file or directory\n", 2);
		else
			ft_putstr_fd(": permission denied\n", 2);
	}
}

void		ft_exec_builtin_cd(t_msh_command *cmd)
{
	char	cwd_fmt[1024];
	char	*new_dir_path;

	if (!(cmd->prog_prms[0] && cmd->prog_prms[1]))
	{
		if (g_msh_params->home_fmt)
			ft_change_dir(g_msh_params->home_fmt);
	}
	else if (cmd->prog_prms[1][0] == '/')
		ft_change_dir(cmd->prog_prms[1]);
	else if (ft_strcmp(cmd->prog_prms[1], "-") == 0)
		ft_change_dir(g_msh_params->prev_location);
	else if (cmd->prog_prms[1])
	{
		if (!(getcwd(cwd_fmt, sizeof(cwd_fmt))))
			ft_putstr_fd("minishell: .: permission denied\n", 2);
		else
		{
			new_dir_path = ft_strjoin_path(cwd_fmt, cmd->prog_prms[1]);
			ft_change_dir(new_dir_path);
		}
	}
	free(g_msh_params->prev_location);
	g_msh_params->prev_location = ft_strdup(g_msh_params->cwd_fmt);
	ft_update_path_value(g_msh_params->cur_environ, "OLDPWD", \
		g_msh_params->prev_location);
	ft_refresh_cwd_env();
}