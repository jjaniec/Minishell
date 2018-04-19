/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork_and_start.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 15:04:13 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 15:04:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Fork current process,
** exec found executable with child and wait
** with parent process,
** if exit on failure is set, kill child process with exit if
** execve fails
*/

void		ft_fork_and_start(char *prog_path, char **prog_params, \
					char **prog_env, int exit_on_failure)
{
	if (0 == (g_cur_process->pid = fork()))
	{
		if (-1 == execve(prog_path, prog_params, prog_env))
		{
			ft_putstr_fd("minishell: exec format error\n", 2);
			if (exit_on_failure)
				exit(1);
		}
	}
	ft_wait_pid(g_cur_process->pid);
	g_cur_process->pid = 0;
}
