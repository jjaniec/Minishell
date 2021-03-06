/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_can_exec_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 18:16:28 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/13 15:46:54 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Return 0 if found executable can be launched, otherwise return 1
*/

int		ft_can_exec_path(t_msh_command *cmd, char *path)
{
	if (cmd && path)
	{
		if (cmd->stats_rcode < 0)
		{
			ft_handle_err_code(2, cmd->prog_name);
			return (0);
		}
		return (ft_handle_err(cmd));
	}
	return (0);
}
