/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_unsetenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:06:47 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 22:47:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Unset an environnement variable of env
*/

static char		*ft_locate_env_var(char *name)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while (g_msh_params->cur_environ[++i])
		if (ft_strcmp(name, g_msh_params->cur_environ[i]) == -61)
		{
			s = g_msh_params->cur_environ[i];
			break ;
		}
	return (s);
}

void			ft_msh_unsetenv(char *name)
{
	int		i;
	int		j;
	char	*s;
	char	**new_env;

	i = -1;
	if (g_msh_params->cur_environ && (s = ft_locate_env_var(name)))
	{
		if (g_msh_params->cur_environ[0] && !g_msh_params->cur_environ[1])
		{
			free(g_msh_params->cur_environ[0]);
			free(g_msh_params->cur_environ[1]);
			free(g_msh_params->cur_environ);
			g_msh_params->cur_environ = NULL;
		}
		else
		{
			while (g_msh_params->cur_environ[++i])
				;
			new_env = malloc(sizeof(char *) * i);
			new_env[i - 1] = NULL;
			i = -1;
			j = 0;
			while (g_msh_params->cur_environ[++i])
				if (g_msh_params->cur_environ[i] != s)
					new_env[j++] = g_msh_params->cur_environ[i];
				else
					free(g_msh_params->cur_environ[i]);
			free(g_msh_params->cur_environ);
			g_msh_params->cur_environ = new_env;
		}
	}
}
