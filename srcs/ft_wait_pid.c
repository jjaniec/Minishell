/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:00:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 12:18:29 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Wait for executed program completion
*/

unsigned int		ft_wait_pid(pid_t pid)
{
	int				status;

	g_cur_process->pid = pid;
	ft_handle_child_sigint(g_msh_params->input->pid);
	while (0 == waitpid(pid, &status, WNOHANG))
		wait(&status);
	g_cur_process->pid = 0;
	return (0);
}
