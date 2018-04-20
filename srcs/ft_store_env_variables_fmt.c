/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_store_env_variables_fmt.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 18:53:00 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 21:53:46 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Get path environnement variable data and store each entry in a char *
*/

static void		ft_store_path_fmt(t_msh_params *msh_params, char *s)
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
			msh_params->path[index++] = entry;
			if (!s2[i])
				break ;
			j = i + 1;
		}
	}
	free(s2);
	msh_params->path[index] = NULL;
}

/*
** Store usefull environnement variable in our global structure
*/

void			ft_store_env_variables_fmt(t_msh_params *msh_params)
{
	int		i;

	i = -1;
	if (msh_params->cur_environ)
		while (msh_params->cur_environ[++i])
		{
			if (ft_strcmp("PATH", msh_params->cur_environ[i]) == -61)
				ft_store_path_fmt(msh_params, msh_params->cur_environ[i]);
			else if (ft_strcmp("PWD", msh_params->cur_environ[i]) == -61)
			{
				msh_params->cwd_fmt = \
					ft_get_path_var_val(\
						&(msh_params->cur_environ[i]), "PWD");
				msh_params->cwd_env = msh_params->cur_environ[i];
			}
			else if (ft_strcmp("HOME", msh_params->cur_environ[i]) == -61)
				msh_params->home_fmt = \
					ft_get_path_var_val(\
						&(msh_params->cur_environ[i]), "HOME");
			else if (ft_strcmp("USER", msh_params->cur_environ[i]) == -61)
				msh_params->user = \
					ft_get_path_var_val(\
						&(msh_params->cur_environ[i]), "USER");
		}
}

void			ft_refresh_fmt_ptrs(t_msh_params *msh_params)
{
	int		i;

	i = -1;
	while (msh_params->path[++i])
	{
		free(msh_params->path[i]);
		msh_params->path[i] = NULL;
	}
	msh_params->cwd_fmt = NULL;
	msh_params->cwd_env = NULL;
	msh_params->home_fmt = NULL;
	msh_params->user = NULL;
	ft_store_env_variables_fmt(msh_params);
}
