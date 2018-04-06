/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_prog_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 19:21:17 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/06 20:42:38 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Count number of options/arguments passed for the program
*/

static int		ft_count_params(char *s)
{
	int		i;
	int		r;

	r = 0;
	i = 0;
	while (s[i] && ft_is_ifs(s[i]))
		i++;
	while (s[i] && !ft_is_ifs(s[i]))
		i++;
	while (s[i] && ft_is_ifs(s[i]))
		i++;
	while (s[i])
	{
		while (s[i] && !ft_is_ifs(s[i]))
			i++;
		while (s[i] && ft_is_ifs(s[i]))
			i++;
		if (s[i])
			i++;
		r++;
	}
	return (r);
}

/*
** Init the char ** containing options/parameters and fill
** each pointer with ft_parse_prog_param_nb
*/

char			**ft_parse_prog_params(char *s, t_msh_command *input)
{
	char	**r;
	int		params_l;
	int		i;

	params_l = ft_count_params(s) + 1;
	r = NULL;
	i = -1;
	if (params_l > 1)
	{
		r = malloc(sizeof(char *) * (params_l + 2));
		r[0] = input->prog_name;
		r[params_l] = 0;
		while (++i < params_l)
			r[i + 1] = ft_parse_prog_param_nb(s, i + 2);
	}
	return (r);
}