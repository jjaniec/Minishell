/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:52:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 19:22:57 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_msh_params	*g_msh_params;


int		main(void)
{
	int		blt;

	g_msh_params = ft_create_msh_params_struct();
	ft_store_env_variables_fmt();
	while (1)
	{
		ft_print_prompt();
		g_msh_params->input = ft_parse_input();
		if (g_msh_params->input)
		{
			ft_debug_g_msh_params();
			if ((blt = ft_is_builtin(g_msh_params->input)) == 2)
				break ;
			else if (blt == 0)
				ft_start_prog();
		}
	}
	return (0);
}
