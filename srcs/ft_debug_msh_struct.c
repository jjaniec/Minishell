/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_msh_struct.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 18:22:03 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 22:22:22 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Print all command parameters passed in stdin
*/

static void		ft_debug_msh_prog_params(t_msh_params *msh_params)
{
	int				i;

	i = -1;
	while (msh_params->input->prog_prms[++i])
	{
		PRINTF("\t\t->prog_prms[%d]: |%s|\n", \
			i, msh_params->input->prog_prms[i]);
	}
}

/*
** Prints content of the global t_msh_params struct
*/

static void		ft_debug_path(t_msh_params *msh_params)
{
	int		i;

	i = -1;
	while (msh_params->path[++i])
		PRINTF("\t\tmsh_params->path[%d]: |%s|\n", i, msh_params->path[i]);
}

void			ft_debug_msh_params(t_msh_params *msh_params)
{
	PRINTF("Content of g_msg_params:\n");
	if (msh_params->input)
	{
		PRINTF("\tContent of msh_params->input:\n");
		PRINTF("\t\t->prog_name: |%s|\n", msh_params->input->prog_name);
		if (msh_params->input->prog_prms)
			ft_debug_msh_prog_params(msh_params);
		else
			PRINTF("\t\t->prog_params: |(null)|\n");
	}
	PRINTF("\tmsh_params->input_r: %d\n", msh_params->input_r);
	PRINTF("\tmsh_params->path:\n");
	ft_debug_path(msh_params);
	PRINTF("\tmsh_params->cwd_fmt: |%s|\n", msh_params->cwd_fmt);
	PRINTF("\tmsh_params->home_fmt: |%s|\n", msh_params->home_fmt);
	PRINTF("\tmsh_params->user: |%s|\n", msh_params->user);
}
