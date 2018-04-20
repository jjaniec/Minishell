/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_msh_struct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 13:45:31 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/16 22:59:02 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	ft_free_ptr_tab(void **ptr)
{
	int		i;

	i = -1;
	while (ptr[++i])
		ft_free_ptr(&(ptr[i]));
}

/*
** Free content of a t_msh_command struct
*/

void	ft_free_msh_command(t_msh_command *mc)
{
	if (mc && mc->prog_prms)
		ft_free_ptr_tab((void **)mc->prog_prms);
	if (mc->prog_stats)
		free(mc->prog_stats);
	ft_free_ptr((void **)&(mc->prog_prms));
	free(mc);
}

/*
** Free content of a t_msh_params struct
*/

void	ft_free_msh_params(t_msh_params *mp)
{
	int		i;

	i = -1;
	while (mp->cur_environ && mp->cur_environ[++i])
		ft_free_ptr((void **)&(mp->cur_environ[i]));
	free(mp->cur_environ);
	mp->cur_environ = NULL;
	i = -1;
	while (mp->path[++i])
		ft_free_ptr((void **)&(mp->path[i]));
	ft_free_ptr((void **)&(mp->prev_location));
	ft_free_ptr((void **)&mp);
}
