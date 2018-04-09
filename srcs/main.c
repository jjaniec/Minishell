/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:52:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/09 17:52:57 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_msh_params	*g_msh_params;

int		main(void)
{
	g_msh_params = ft_create_msh_params_struct();
	ft_store_env_variables();
	while (1)
	{
		ft_print_prompt();
		g_msh_params->input = ft_parse_input();
		if (g_msh_params->input)
		{
			//ft_store_env_variables();
			ft_debug_g_msh_params();
			if (g_msh_params->input && g_msh_params->input->prog_name && \
				ft_strcmp(g_msh_params->input->prog_name, "exit") == 0)
				break ;
			else
				ft_start_prog();
		}
	}
	return (0);
}
