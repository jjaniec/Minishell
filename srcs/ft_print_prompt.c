/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:33:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/17 13:19:44 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		ft_print_cur_dir(void)
{
	char			cur_path_fmt[1024];
	struct stat		home_stats;
	int				i;

	i = 0;
	if (!(getcwd(cur_path_fmt, sizeof(cur_path_fmt))))
		ft_putstr_fd("\e[31mUnknown path ¯\\_(ツ)_/¯\n\e[39m", 2);
	else
	{
		if (g_msh_params->home_fmt && \
			ft_strstr(cur_path_fmt, g_msh_params->home_fmt) && \
			!(stat(cur_path_fmt, &home_stats)))
		{
			while (cur_path_fmt[i] == g_msh_params->home_fmt[i] && \
				g_msh_params->home_fmt[i])
				i++;
			PRINTF("\e[34m~%s\e[39m\n", cur_path_fmt + i);
		}
		else
			PRINTF("\e[34m%s\e[39m\n", cur_path_fmt);
	}
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
