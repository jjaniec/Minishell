/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 14:52:41 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/19 22:25:45 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_process		*g_cur_process;

t_msh_params	*g_msh_params;

/*
** Main loop,
** wait for input, parse command and arguments in a s_msh_command struct,
** exec command and it's arguments with ft_start_prog or exec builtin,
** free created s_msh_command struct and repeat while a SIGINT is not received
*/

static void		ft_msh_loop(t_msh_params *msh_params)
{
	int		blt;

	while (1)
	{
		ft_print_prompt(msh_params);
		if (signal(SIGINT, ft_sigint_handler) == SIG_ERR)
			PRINTF("minishell: failed to catch SIGINT\n");
		msh_params->input = ft_parse_input();
		if (msh_params->input && msh_params->input->prog_name)
		{
			if ((blt = ft_is_builtin(msh_params, msh_params->input)) == 2)
			{
				ft_free_msh_command(msh_params->input);
				break ;
			}
			else if (blt == 0)
				ft_start_prog(msh_params);
		}
		if (msh_params->input)
			ft_free_msh_command(msh_params->input);
	}
}

/*
** Init s_msh_params to store a dump of environnement variables,
** and pointers to most used variables (path, pwd, home),
** then start main loop
*/

int				main(int ac, char **av, char **environ)
{
	t_msh_params	*msh_params;

	(void)ac;
	(void)av;
	g_cur_process = malloc(sizeof(t_process));
	g_cur_process->pid = 0;
	msh_params = ft_create_msh_params_struct(environ);
	g_msh_params = msh_params;
	ft_store_env_variables_fmt(msh_params);
	ft_msh_loop(msh_params);
	ft_free_msh_params(msh_params);
	free(g_cur_process);
	return (0);
}
