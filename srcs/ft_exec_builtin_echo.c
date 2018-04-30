/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_builtin_echo.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaniec <jjaniec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 18:18:05 by jjaniec           #+#    #+#             */
/*   Updated: 2018/04/30 13:24:23 by jjaniec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Prints content of environnement variables w/ ft_get_path_var_val,
** if env variable is not found, ft_get_path_var_val returns NULL
** and the function prints nothing
*/

static void	ft_print_env_var_content(t_msh_params *msh_params, char *var)
{
	char		*content;

	content = ft_get_path_var_val(msh_params->cur_environ, var);
	if (content)
		PRINTF("%s", content);
}

/*
** Print characters before '$',
** once '$' is found, if there is no other '$' in the rest of the string,
** print content of environnement variable (s[i] + 1)
** w/ ft_print_env_var_content
** otherwise if another '$' is found and we need to print
** more than 1 env variable,
** next_var_ptr will be pointing to the next character '$',
** we replace *next_var_ptr to '\0' temporarily to pass (s + i) as
** an environnement variable name to ft_print_env_var_content,
** *next_var_ptr is then re-assigned to '$'
** and we recurse the function with next_var_ptr as new string
*/

static void	ft_echo_env_variables(t_msh_params *msh_params, char *s)
{
	char		*next_var_ptr;
	int			i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && s[i] != '$')
		ft_putchar(s[i++]);
	next_var_ptr = ft_strchr(s + ((i + 1) * sizeof(char)), '$');
	if (next_var_ptr)
	{
		*next_var_ptr = '\0';
		ft_print_env_var_content(msh_params, s + (i + 1) * sizeof(char));
		*next_var_ptr = '$';
		ft_echo_env_variables(msh_params, next_var_ptr);
		return ;
	}
	else
		ft_print_env_var_content(msh_params, s + (i + 1) * sizeof(char));
}

/*
** Prints content of echo params, if a $ is found,
** print content of env variable instead with ft_echo_env_variables()
*/

void		ft_exec_builtin_echo(t_msh_params *msh_params, t_msh_command *cmd)
{
	int		i;
	char	*ptr;

	i = 0;
	if (cmd->prog_prms && cmd->prog_prms[0])
	{
		while (cmd->prog_prms[++i])
		{
			ptr = ft_strchr(cmd->prog_prms[i], '$');
			ptr = (ptr && *ptr) ? (ptr + sizeof(char)) : (NULL);
			if (ptr && *ptr)
			{

				ft_echo_env_variables(msh_params, cmd->prog_prms[i]);
				if (i == 1)
					PRINTF(" ");
			}
			else
				PRINTF((i == 1) ? ("%s") : (" %s"), cmd->prog_prms[i]);
		}
	}
	PRINTF("\n");
}
