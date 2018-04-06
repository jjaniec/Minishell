/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_start_prog.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/06 20:01:56 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/06 20:22:18 by jjaniec          ###   ########.fr       */
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
		return (NULL);
	return (s);
}

void			ft_start_prog(void)
{
	int		i;
	char	*prog_abs_path;

	i = -1;
	while (g_msh_params->path[++i])
		if ((prog_abs_path = ft_is_path_valid(g_msh_params->path[i])))
		{
			execve(prog_abs_path, g_msh_params->input->prog_prms, environ);
			free(prog_abs_path);
		}
}