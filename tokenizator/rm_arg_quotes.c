/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_arg_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:37 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/03 16:41:54 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**cmd_arg_quottes(char	*pipe)
{
	char	**aux_cmd;
	char	*aux;
	int		x;

	//printf("	%p\n", pipe);
	aux = NULL;
	if (!pipe)
		return (NULL);
	//printf("cmd_arg_quotes -> %p\n", pipe);
	aux_cmd = spqu_split(skip_spaces(pipe), ' ');
	//system("leaks minishell");
	//for (int i = 0; aux_cmd[i]; i++) printf("	%s\n", aux_cmd[i]);
	x = -1;
	while (aux_cmd[++x] != NULL)
	{
		if (aux_cmd[x][0] != '$' && aux_cmd[x][0] != '<')
			aux = skip_quotes(skip_spaces(aux_cmd[x]));
		else
			aux = skip_spaces(aux_cmd[x]);
		free(aux_cmd[x]);
		aux_cmd[x] = aux;
	}
	return (aux_cmd);
}