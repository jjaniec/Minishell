/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_env_variables_fmt.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:53:00 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 16:33:42 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Get path environnement variable data and store each entry in a char *
*/

static void		ft_store_path_fmt(char *s)
{
	char		*s2;
	int			i;
	int			j;
	int			index;
	char		*entry;

	i = -1;
	j = 0;
	index = 0;
	s2 = ft_strsub(s, 5, ft_strlen(s) - 5);
	while (++i || 1)
	{
		if (s2[i] == ':' || !s2[i])
		{
			entry = ft_strsub(s2, j, i - j);
			g_msh_params->path[index++] = entry;
			if (!s2[i])
				break ;
			j = i + 1;
		}
	}
	free(s2);
	g_msh_params->path[index] = NULL;
}

void			ft_store_cwd_fmt(char *cwd_env_ptr)
{
	if (cwd_env_ptr && ft_strlen(cwd_env_ptr) >= 4)
		g_msh_params->cwd_fmt = cwd_env_ptr + 4;
	else
		g_msh_params->cwd_fmt = NULL;
}

/*
** Store usefull environnement variable in our global structure
*/

void			ft_store_env_variables_fmt(void)
{
	int		i;

	i = -1;
	if (g_msh_params->cur_environ)
		while (g_msh_params->cur_environ[++i])
		{
			if (ft_strcmp("PATH", g_msh_params->cur_environ[i]) == -61)
				ft_store_path_fmt(g_msh_params->cur_environ[i]);
			else if (ft_strcmp("PWD", g_msh_params->cur_environ[i]) == -61)
			{
				g_msh_params->cwd_fmt = \
					ft_get_path_var_val(&(g_msh_params->cur_environ[i]), "PWD");
				g_msh_params->cwd_env = g_msh_params->cur_environ[i];
			}
			else if (ft_strcmp("HOME", g_msh_params->cur_environ[i]) == -61)
				g_msh_params->home_fmt = \
					ft_get_path_var_val(&(g_msh_params->cur_environ[i]), "HOME");
			else if (ft_strcmp("USER", g_msh_params->cur_environ[i]) == -61)
				g_msh_params->user = \
					ft_get_path_var_val(&(g_msh_params->cur_environ[i]), "USER");
		}
}

void			ft_refresh_fmt_ptrs(void)
{
	int		i;

	i = -1;
	while (g_msh_params->path[++i])
	{
		free(g_msh_params->path[i]);
		g_msh_params->path[i] = NULL;
	}
	g_msh_params->cwd_fmt = NULL;
	g_msh_params->cwd_env = NULL;
	g_msh_params->home_fmt = NULL;
	g_msh_params->user = NULL;
	ft_store_env_variables_fmt();
}
