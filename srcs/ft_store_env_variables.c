/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_env_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:53:00 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/06 19:43:19 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Get path environnement variable data and store each entry in a char *
*/

static void		ft_store_path(char *s)
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

/*
** Store usefull environnement variable in our global structure
*/

void			ft_store_env_variables(void)
{
	int		i;

	i = -1;
	while (environ[++i])
	{
		if (ft_strcmp("PATH", environ[i]) == -61)
			ft_store_path(environ[i]);
		else if (ft_strcmp("PWD", environ[i]) == -61)
			g_msh_params->cwd = environ[i];
		else if (ft_strcmp("HOME", environ[i]) == -61)
			g_msh_params->home = environ[i];
		//PRINTF("environ[%d] -> %s\n", i, environ[i]);
	}
}
