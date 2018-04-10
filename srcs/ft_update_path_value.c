/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_update_path_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 19:34:27 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 19:44:11 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
**
*/

char	*ft_update_path_value(char **path, char *var_name, char *data)
{
	int		i;
	char	*s;

	i = 0;
	while (path[i] && ft_strcmp(var_name, path[i]) != -61)
		i++;
	if (path[i])
	{
		s = ft_strsub(path[i], 0, ft_strlen(var_name) + 1);
		s = ft_strjoin(s, data);
		free(path[i]);
		path[i] = s;
		return (s);
	}
	return (NULL);
}