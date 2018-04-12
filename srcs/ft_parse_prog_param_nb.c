/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_prog_param_nb.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:41:17 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/05 21:43:04 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Return 1 if c != '\0' && c is a field separator
*/

int					ft_is_ifs(char c)
{
	if (!c)
		return (0);
	return (ft_strchr(IFS, c) ? (1) : (0));
}

/*
** Parse option/parameter $nb between IFS values
*/

char				*ft_parse_prog_param_nb(char *str, int nb)
{
	int				i;
	int				j;
	char			*ret;

	ret = NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && ft_is_ifs(str[i]))
			i++;
		if (!str[i])
			return (NULL);
		j = i;
		while (str[j] && !ft_is_ifs(str[j]))
			j++;
		if (nb == 1)
			return (ft_strsub(str + i, 0, j - i));
		i = j;
		nb--;
	}
	return (ret);
}
