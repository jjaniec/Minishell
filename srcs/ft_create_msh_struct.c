/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_msh_struct.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:40:55 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/06 19:48:35 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Creates a prog_param struct and set it's next to NULL
*/

t_prog_param		*ft_create_prog_param_elem(void)
{
	t_prog_param	*e;

	if (!(e = malloc(sizeof(t_prog_param))))
	{
		ft_putstr_fd("Malloc error - abort\n", 2);
		exit(2);
	}
	e->prm = NULL;
	e->next = NULL;
	return (e);
}

/*
** Creates a msh_params struct and init it's elems
*/

t_msh_params		*ft_create_msh_params_struct(void)
{
	t_msh_params	*e;

	if (!(e = malloc(sizeof(t_msh_params))))
	{
		ft_putstr_fd("Malloc error - abort\n", 2);
		exit(2);
	}
	e->input = NULL;
	e->input_r = -255;
	e->cwd = NULL;
	e->home = NULL;
	return (e);
}
