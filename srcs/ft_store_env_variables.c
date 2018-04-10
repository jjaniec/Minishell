/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_env_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:53:00 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 19:10:18 by jjaniec          ###   ########.fr       */
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
	while (environ[++i])
	{
		if (ft_strcmp("PATH", environ[i]) == -61)
			ft_store_path_fmt(environ[i]);
		else if (ft_strcmp("PWD", environ[i]) == -61)
			ft_store_cwd_fmt(environ[i]);
		else if (ft_strcmp("HOME", environ[i]) == -61)
			g_msh_params->home_fmt = environ[i] + 5;
		else if (ft_strcmp("USER", environ[i]) == -61)
			g_msh_params->user = environ[i] + 5;
	}
}
