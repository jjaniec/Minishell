/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 16:47:51 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 17:48:31 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Check if passed command is a builtin or not,
** if yes it returns 1 to break the main loop,
** otherwise return 0 to look for executable with path entries
*/

int		ft_is_builtin(t_msh_command *cmd)
{
	int		blt;

	if (cmd && cmd->prog_name)
	{
		if (ft_strcmp(g_msh_params->input->prog_name, "exit") == 0)
			return (2);
		else if ((\
			(ft_strcmp(g_msh_params->input->prog_name, "echo") == 0 && \
				(blt = 1)) || \
			(ft_strcmp(g_msh_params->input->prog_name, "cd") == 0 && \
				(blt = 2)) || \
			(ft_strcmp(g_msh_params->input->prog_name, "setenv") == 0 && \
				(blt = 3)) || \
			(ft_strcmp(g_msh_params->input->prog_name, "unsetenv") == 0 && \
				(blt = 4)) || \
			(ft_strcmp(g_msh_params->input->prog_name, "env") == 0 && \
				(blt = 5))))
		{
			ft_exec_builtin(blt, cmd);
			return (1);
		}
	}
	return (0);
}
