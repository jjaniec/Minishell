/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:18:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/09 20:29:13 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Totally not inspired by
** https://github.com/hkbakke/bash-insulter
*/

void	ft_print_err_head(char *s)
{
	ft_putstr_fd("\n   \e[91m", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\e[39m", 2);
}

/*
** Prints command not found error message
*/

void	ft_err_cmd_not_found(t_msh_command *cmd)
{
	ft_print_err_head("Pro tip: type a valid command!\n\n");
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd->prog_name, 2);
	ft_putchar_fd(2, '\n');
}
