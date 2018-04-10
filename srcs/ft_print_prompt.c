/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:33:19 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 18:22:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_print_cur_dir(char *cwd, char *home)
{
	if (ft_strstr(cwd, home))
		PRINTF("\e[34m~%s\e[39m\n", cwd + ft_strlen(home));
	else
		PRINTF("\e[34m%s\e[39m\n", cwd);
}

/*
** Prints minishell's prompt
*/

void		ft_print_prompt(void)
{
	write(1, "\n", 1);
	ft_print_cur_dir(g_msh_params->cwd, g_msh_params->home);
	write(1, "❯ ", 4);
}
