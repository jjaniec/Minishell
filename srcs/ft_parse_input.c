/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_take_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/05 15:31:18 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/05 19:15:12 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char			*ft_read_fd(int fd, ssize_t *n)
{
	char	*s;
	ssize_t	n_cur;

	s = malloc(sizeof(char) * 256);
	s[255] = '\0';
	n_cur = read(fd, s, 255);
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
** Prints prompt and parse input in a t_msh_params struct
*/

static int			ft_is_ifs(char c)
{
	int		i;

	i = 0;
	while (IFS[i] && IFS[i] != c)
		i++;
	return ((IFS[i] == c) ? (1) : (0));
}

t_prog_param		*ft_parse_prog_param_nb(char *str, int nb)
{
	int				i;
	int				j;
	t_prog_param	*e;

	e = NULL;
	i = 0;
	while (str[i] && nb != 0)
	{
		while (str[i] && ft_is_ifs(str[i]))
			i++;
		if (!str[i])
			return (NULL);
		j = i;
		while (!ft_is_ifs(str[j]))
			j++;
		nb--;
	}
	e = ft_create_prog_param_elem();
	e->prm = ft_strsub(str, i, j);
	return (e);
}

t_msh_command		*ft_parse_input(void)
{
	t_msh_command	*content;
	char			*s;
	int				i;
	ssize_t			n;

	n = 0;
	i = -1;
	s = ft_read_fd(0, &n);
	PRINTF("n : %zd\n", n);
	if (n > 0 && s && (content = malloc(sizeof(t_msh_command))))
	{
		ft_printf("s : |%s|\n", s);
		while (!ft_is_ifs(s[++i]))
			;
		content->prog_name = ft_strsub(s, 0, i);
		content->prog_prm = ft_parse_prog_param_nb(s + i, 1);
		content->next = NULL;
		return (content);
	}
	return (NULL);
}
