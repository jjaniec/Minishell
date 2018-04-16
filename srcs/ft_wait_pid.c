/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:00:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 13:38:41 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Wait for executed program completion
*/

int		ft_wait_pid(pid_t pid)
{
	int				status;

	ft_handle_child_sigint();
	while (0 == waitpid(pid, &status, WNOHANG))
		wait(&status);
	return (0);
}
