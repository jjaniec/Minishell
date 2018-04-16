/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_path_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 19:34:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 20:57:46 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Change the value of $var_name in $path,
** if $var_name is not found, return NULL
** otherwise return the address of $var_name
*/

char	*ft_update_path_value(char **path, char *var_name, char *data)
{
	int		i;
	char	*s;
	char	*tmp;

	i = 0;
	while (path && path[i] && ft_strcmp(var_name, path[i]) != -61)
		i++;
	if (path && path[i])
	{
		tmp = ft_strsub(path[i], 0, ft_strlen(var_name) + 1);
		s = ft_strjoin(tmp, data);
		free(path[i]);
		free(tmp);
		path[i] = s;
		return (s);
	}
	return (NULL);
}
