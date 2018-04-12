/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:33:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/12 22:05:56 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_print_cur_dir(char *cwd)
{
	char	*cur_path_fmt;
	char	*new_path_begin;
	int		i;

	new_path_begin = NULL;
	i = -1;
	cur_path_fmt = ft_get_path_var_val(g_msh_params->cur_environ, "PWD");
	if (cur_path_fmt && g_msh_params->home_fmt && \
		ft_strstr(cur_path_fmt, g_msh_params->home_fmt))
	{
		while (cur_path_fmt[i] == g_msh_params->home_fmt[i])
			i++;
		PRINTF("\e[34m~%s\e[39m\n", cur_path_fmt + i);
	}
	else
		PRINTF("\e[34m%s\e[39m\n", cwd);
}

/*
** Prints minishell's prompt
*/

void		ft_print_prompt(void)
{
	write(1, "\n", 1);
	ft_print_cur_dir(g_msh_params->cwd_fmt);
	write(1, "❯ ", 4);
}
