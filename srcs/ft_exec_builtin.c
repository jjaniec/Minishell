/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:31:48 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 22:44:10 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		ft_exec_builtin_echo(t_msh_command *cmd)
{
	int		i;

	i = 0;
	if (cmd->prog_prms && cmd->prog_prms[0])
	{
		while (cmd->prog_prms[++i])
			PRINTF((i == 1) ? ("%s") : (" %s"), cmd->prog_prms[i]);
	}
	PRINTF("\n");
}

static void		ft_exec_builtin_env(void)
{
	int		i;

	i = -1;
	while (g_msh_params->cur_environ[++i])
		PRINTF("%s\n", g_msh_params->cur_environ[i]);
}

/*
** Execute builtin number $blt
*/

void			ft_exec_builtin(int blt, t_msh_command *cmd)
{
	if (blt == 1)
		ft_exec_builtin_echo(cmd);
	else if (blt == 5)
		ft_exec_builtin_env();
	else if (blt == 2)
		ft_exec_builtin_cd(cmd);
}
