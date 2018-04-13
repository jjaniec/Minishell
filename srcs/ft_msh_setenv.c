/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:55:21 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/13 16:53:01 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Create or change an environnement variable
*/

void	ft_msh_setenv(char *name, char *value, int overwrite)
{
	int		i;
	char	*s;
	char	*tmp;
	char	*new;
	char	**old_env;

	i = -1;
	s = NULL;
	while (g_msh_params->cur_environ[++i])
		if (ft_strcmp(name, g_msh_params->cur_environ[i]) == -61)
		{
			s = g_msh_params->cur_environ[i];
			break ;
		}
	if (!(s && !overwrite))
	{
		tmp = ft_strjoin(name, "=");
		new = ft_strjoin(tmp, value);
		if (s)
		{
			free(g_msh_params->cur_environ[i]);
			g_msh_params->cur_environ[i] = new;
		}
		else
		{
			old_env = g_msh_params->cur_environ;
			g_msh_params->cur_environ = \
				ft_add_ptr_to_tab(g_msh_params->cur_environ, new);
			free(old_env);
		}
		free(tmp);
		free(new);
	}
}
