/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path_var_val.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/12 21:04:55 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/13 13:44:26 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Return value of a path variable
*/

char		*ft_get_path_var_val(char **env, char *var)
{
	int		i;
	int		j;
	char	*r;

	r = NULL;
	i = -1;
	if (!env)
		return (r);
	while (env[++i])
		if (ft_strcmp(var, env[i]) == -61)
		{
			j = 0;
			while (env[i][j++])
				if (env[i][j] == '=')
					r = env[i] + j + 1;
			break ;
		}
	//PRINTF("val of %s : |%s|\n", var, r);
	return (r);
}