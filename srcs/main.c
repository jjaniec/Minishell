/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:52:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/05 19:15:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_msh_params	*g_msh_params;

int		main(void)
{
	g_msh_params = ft_create_msh_params_struct();
	while (1)
	{
		ft_print_prompt();
		g_msh_params->input = ft_parse_input();
		ft_debug_g_msh_params();
		if (g_msh_params->input && \
			ft_strcmp(g_msh_params->input->prog_name, "exit") == 0)
			break ;
	}
	return (0);
}
