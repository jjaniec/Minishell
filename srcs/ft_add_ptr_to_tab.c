/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_ptr_to_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 19:10:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 19:26:09 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Creates a copy of a char ** and malloc all it's elements,
** used to create a dump of all environnement variables in environ when !e
** or to add a ptr to a tab of ptr
*/

char		**ft_add_ptr_to_tab(char **tab, char *e)
{
	int		i;
	char	**r;

	r = NULL;
	i = -1;
	while (tab[++i])
		;
	if (i > 0)
	{
		r = malloc(sizeof(char *) * (i + ((e) ? (2) : (1))));
		i = -1;
		while (tab[++i])
			r[i] = ft_strdup(tab[i]);
		r[i] = ((e) ? (ft_strdup(e)) : (e));
	}
	return (r);
}