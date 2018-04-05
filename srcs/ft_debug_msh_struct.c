/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_msh_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:22:03 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/05 20:09:28 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Print all command parameters passed in stdin
*/

void		ft_debug_msh_prog_params(void)
{
	int				i;

	i = -1;
	while (g_msh_params->input->prog_prms[++i])
	{
		PRINTF("\t\t->prog_prms[%d]: |%s|\n", i, g_msh_params->input->prog_prms[i]);
	}
}

/*
** Prints content of the global t_msh_params struct
*/

void		ft_debug_g_msh_params(void)
{
	PRINTF("Content of g_msg_params:\n");
	if (g_msh_params->input)
	{
		PRINTF("\tContent of g_msh_params->input:\n");
		PRINTF("\t\t->prog_name: |%s|\n", g_msh_params->input->prog_name);
		if (g_msh_params->input->prog_prms)
			ft_debug_msh_prog_params();
		else
			PRINTF("\t\t->prog_params: |(null)|\n");
	}
	PRINTF("\tg_msh_params->input_r: %d\n", g_msh_params->input_r);
	PRINTF("\tg_msh_params->cwd: |%s|\n", g_msh_params->cwd);
}