/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_sig.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 21:20:53 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 18:11:49 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Handler to pass to signal when calling it,
** if pid is set to 0, re-print prompt, otherwise kill pid as it will
** be the child's one and print error message
*/

void				ft_sigint_handler(int signo)
{
	if (signo == SIGINT && g_cur_process->pid)
	{
		kill(g_cur_process->pid, SIGINT);
		ft_putstr_fd("\nminishell: ", 2);
		ft_putstr_fd(g_msh_params->input->prog_name, 2);
		ft_putstr_fd(": canceled by user (SIGINT)\n", 2);
	}
	else if (signo == SIGINT && !g_cur_process->pid)
	{
		ft_putchar('\n');
		ft_print_prompt();
	}
}

/*
** Initialize handler for sigint signals
*/

void				ft_handle_child_sigint(void)
{
	if (signal(SIGINT, ft_sigint_handler) == SIG_ERR)
		PRINTF("minishell: failed to catch SIGINT\n");
}
