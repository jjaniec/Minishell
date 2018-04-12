/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 20:18:44 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/10 16:19:54 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Totally not inspired by
** https://github.com/hkbakke/bash-insulter
*/

static void	ft_print_err_head(char *s)
{
	ft_putstr_fd("\n   \e[91m", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\e[39m", 2);
}

/*
** Prints command not found error message
*/

void		ft_err_cmd_not_found(t_msh_command *cmd)
{
	ft_print_err_head("Pro tip: type a valid command!\n\n");
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(cmd->prog_name, 2);
	ft_putchar_fd(2, '\n');
}

/*
** Search in st_mode if passed program is a directory or non executable
*/

void		ft_handle_err_code(int err, char *prog_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(prog_name, 2);
	if (err == 1)
		ft_putstr_fd(": is a directory\n", 2);
	else if (err == 2)
		ft_putstr_fd(": permission denied\n", 2);
}

int			ft_handle_err(t_msh_command *cmd)
{
	int		err;

	err = 0;
	if (cmd && cmd->prog_stats)
	{
		if (S_ISDIR(cmd->prog_stats->st_mode))
			ft_handle_err_code((err = 1), cmd->prog_name);
		else if (!(cmd->prog_stats->st_mode & S_IXUSR))
			ft_handle_err_code((err = 2), cmd->prog_name);
	}
	return (err);
}
