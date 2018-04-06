/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_env_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:53:00 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/06 19:33:09 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Get path environnement variable data
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
			//PRINTF("Entry : %s\n", entry);
			if (!s2[i])
				break ;
			j = i + 1;
		}
	}
	g_msh_params->path[index] = NULL;
}

void			ft_store_env_variables(void)
{
	int		i;

	i = -1;
	while (environ[++i])
	{
		if (ft_strcmp("PATH", environ[i]) == -61)
			ft_store_path(environ[i]);
		//PRINTF("environ[%d] -> %s\n", i, environ[i]);
	}
}
