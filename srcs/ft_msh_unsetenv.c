/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_unsetenv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 18:06:47 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 22:17:33 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Unset an environnement variable of env
*/

static char		*ft_locate_env_var(t_msh_params *msh_params, char *name)
{
	int		i;
	char	*s;

	i = -1;
	s = NULL;
	while (msh_params->cur_environ[++i])
		if (ft_strcmp(name, msh_params->cur_environ[i]) == -61)
		{
			s = msh_params->cur_environ[i];
			break ;
		}
	return (s);
}

static void		ft_del_env(t_msh_params *msh_params)
{
	free(msh_params->cur_environ[0]);
	free(msh_params->cur_environ[1]);
	free(msh_params->cur_environ);
	msh_params->cur_environ = NULL;
}

static void		ft_remake_env(t_msh_params *msh_params, char *s)
{
	int		i;
	int		j;
	char	**new_env;

	i = -1;
	while (msh_params->cur_environ[++i])
		;
	new_env = malloc(sizeof(char *) * i);
	new_env[i - 1] = NULL;
	i = -1;
	j = 0;
	while (msh_params->cur_environ[++i])
		if (msh_params->cur_environ[i] != s)
			new_env[j++] = msh_params->cur_environ[i];
		else
			free(msh_params->cur_environ[i]);
	free(msh_params->cur_environ);
	msh_params->cur_environ = new_env;
}

void			ft_msh_unsetenv(t_msh_params *msh_params, char *name)
{
	char	*s;

	if (msh_params->cur_environ && (s = ft_locate_env_var(msh_params, name)))
	{
		if (msh_params->cur_environ[0] && !msh_params->cur_environ[1])
			ft_del_env(msh_params);
		else
			ft_remake_env(msh_params, s);
	}
}
