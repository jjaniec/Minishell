/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_prog.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:01:56 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/09 18:06:35 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Try to launch value of g_msh_params->prog_name with every path entry
*/

static char		*ft_is_path_valid(char *prog_path)
{
	char	*s;
	struct stat		prog_stats;

	s = ft_strjoin_path(prog_path, g_msh_params->input->prog_name);
	if (lstat(s, &prog_stats) < 0)
	{
		free(s);
		return (NULL);
	}
	return (s);
}

void			ft_start_prog(void)
{
	int		i;
	char	*prog_abs_path;

	i = -1;
	prog_abs_path = NULL;
	while (g_msh_params->path[++i])
		if ((prog_abs_path = ft_is_path_valid(g_msh_params->path[i])))
		{
			if (0 == (g_msh_params->input->pid = fork()) && -1 == \
				execve(prog_abs_path, g_msh_params->input->prog_prms, environ))
				break ;
			ft_wait_pid(g_msh_params->input->pid);
			free(prog_abs_path);
			break ;
		}
}
