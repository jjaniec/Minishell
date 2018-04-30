/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/10 17:31:48 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/27 18:29:06 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void		ft_exec_builtin_env(t_msh_params *msh_params)
{
	int		i;

	i = -1;
	while (msh_params->cur_environ && msh_params->cur_environ[++i])
		PRINTF("%s\n", msh_params->cur_environ[i]);
}

static int		ft_args_count_err(t_msh_command *cmd, int min, int max)
{
	if (cmd->prog_prms_count < min)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->prog_name, 2);
		ft_putstr_fd(": not enough arguments\n", 2);
		return (1);
	}
	if (cmd->prog_prms_count > max)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->prog_name, 2);
		ft_putstr_fd(": too many arguments\n", 2);
		return (1);
	}
	return (0);
}

/*
** Execute builtin number $blt
*/

void			ft_exec_builtin(int blt, t_msh_params *msh_params, \
					t_msh_command *cmd)
{
	if (blt == 1)
		ft_exec_builtin_echo(msh_params, cmd);
	else if (blt == 5)
		ft_exec_builtin_env(msh_params);
	else if (blt == 2 && !ft_args_count_err(cmd, 0, 1))
		ft_exec_builtin_cd(msh_params, cmd);
	else if (blt == 3 && !ft_args_count_err(cmd, 1, 2) && \
		cmd->prog_prms_count == 2)
		msh_params->cur_environ = ft_msh_setenv(msh_params, \
			msh_params->cur_environ, cmd->prog_prms[1], cmd->prog_prms[2]);
	else if (blt == 4 && !ft_args_count_err(cmd, 1, 1))
		ft_msh_unsetenv(msh_params, cmd->prog_prms[1]);
	if (blt == 3 || blt == 4)
		ft_refresh_fmt_ptrs(msh_params);
}
