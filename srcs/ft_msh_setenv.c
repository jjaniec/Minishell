/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msh_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/11 15:55:21 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 17:52:35 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Create or change an environnement variable
*/

static void		ft_msh_change_env_var(char **env, char *name, char *val)
{
	char	*tmp;
	char	*r;
	int		i;

	i = 0;
	tmp = ft_strjoin(name, "=");
	r = ft_strjoin(tmp, val);
	free(tmp);
	while (env[i] && ft_strcmp(name, env[i]) != -61)
		i++;
	free(env[i]);
	env[i] = r;
}

static char		**ft_msh_add_env_var(char **env, char *name, char *val)
{
	char	**r;
	char	*new;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	new = ft_strjoin(tmp, val);
	free(tmp);
	r = ft_add_ptr_to_tab(env, new);
	free(new);
	return (r);
}

char			**ft_msh_setenv(char **env, char *name, \
					char *value, int overwrite)
{
	int		i;
	char	*s;
	char	**new_env;
	char	**old_env;

	i = -1;
	new_env = NULL;
	old_env = g_msh_params->cur_environ;
	s = ft_get_path_var_val(g_msh_params->cur_environ, name);
	if (s && overwrite)
	{
		ft_msh_change_env_var(g_msh_params->cur_environ, name, value);
		return (env);
	}
	if (!s)
	{
		new_env = ft_msh_add_env_var(env, name, value);
		free(env);
		return (new_env);
	}
	return (env);
}
