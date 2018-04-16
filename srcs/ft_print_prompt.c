/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:33:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 21:06:27 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		ft_print_cur_dir(void)
{
	char	*cur_path_fmt;
	int		i;

	i = 0;
	cur_path_fmt = ft_get_path_var_val(g_msh_params->cur_environ, "PWD");
	if (cur_path_fmt && g_msh_params->home_fmt && \
		ft_strstr(cur_path_fmt, g_msh_params->home_fmt))
	{
		while (cur_path_fmt[i] == g_msh_params->home_fmt[i] && \
			g_msh_params->home_fmt[i])
			i++;
		PRINTF("\e[34m~%s\e[39m\n", cur_path_fmt + i);
	}
	else if (cur_path_fmt)
		PRINTF("\e[34m%s\e[39m\n", cur_path_fmt);
}

/*
** Prints minishell's prompt
*/

void			ft_print_prompt(void)
{
	write(1, "\n", 1);
	ft_print_cur_dir();
	write(1, "❯ ", 4);
}
