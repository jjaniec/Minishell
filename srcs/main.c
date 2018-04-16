/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:52:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 18:13:50 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_msh_params	*g_msh_params;

t_process		*g_cur_process;

int		main(void)
{
	int		blt;

	g_cur_process = malloc(sizeof(t_process));
	g_cur_process->pid = 0;
	g_msh_params = ft_create_msh_params_struct();
	ft_store_env_variables_fmt();
	while (1)
	{
		ft_print_prompt();
		if (signal(SIGINT, ft_sigint_handler) == SIG_ERR)
			PRINTF("minishell: failed to catch SIGINT\n");
		g_msh_params->input = ft_parse_input();
		if (g_msh_params->input && g_msh_params->input->prog_name)
		{
			if ((blt = ft_is_builtin(g_msh_params->input)) == 2)
			{
				ft_free_msh_command(g_msh_params->input);
				break ;
			}
			else if (blt == 0)
				ft_start_prog();
		}
		if (g_msh_params->input)
			ft_free_msh_command(g_msh_params->input);
	}
	ft_free_msh_params(g_msh_params);
	free(g_cur_process);
	return (0);
}
