/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait_pid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:00:09 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/09 17:42:32 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Wait for executed program completion,
** returns total duration of program
*/

unsigned int		ft_wait_pid(pid_t pid)
{
	int				status;

	while (0 == waitpid(pid, &status, WNOHANG))
		wait(&status);
	printf("WEXITSTATUS %d WIFEXITED %d [status %d]\n",
		WEXITSTATUS(status), WIFEXITED(status), status);
	return (0);
}
