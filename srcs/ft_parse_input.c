/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:31:18 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/06 20:50:25 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Read entirely stdin
*/

static char			*ft_read_fd(int fd, ssize_t *n)
{
	char	*s;
	ssize_t	n_cur;

	s = malloc(sizeof(char) * 256);
	n_cur = read(fd, s, 255);
	s[n_cur] = '\0';
	if (n_cur == -1)
		return (NULL);
	if (n_cur == 255)
	{
		*n += n_cur;
		return (s = ft_strjoin_free(s, ft_read_fd(fd, n)));
	}
	*n += n_cur;
	return (s);
}

/*
** Make a t_msh_command struct, set target program_name to first element
** betwee IFS values,
** and parse it's options/parameter in a char ** to be passed to execve
*/

static char			**ft_init_prms_no_args(t_msh_command *input)
{
	char		**tab;

	tab = malloc(sizeof(char *) * 2);
	tab[0] = input->prog_name;
	tab[1] = NULL;
	return (tab);
}

t_msh_command		*ft_parse_input(void)
{
	t_msh_command	*input;
	char			*s;
	ssize_t			n;

	s = NULL;
	n = 0;
	s = ft_read_fd(0, &n);
	if (n > 0 && s && ft_strlen(s) >= 1 && (input = malloc(sizeof(t_msh_command))))
	{
		input->prog_name = ft_parse_prog_param_nb(s, 1);
		input->prog_prms = ft_parse_prog_params(s, input);
		if (!input->prog_prms)
			input->prog_prms = ft_init_prms_no_args(input);
		input->next = NULL;
		return (input);
	}
	return (NULL);
}
