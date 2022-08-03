/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:08:38 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/03 16:38:13 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_redirec(char **cmd_sp, int x)
{
	while (cmd_sp[++x] != NULL)
	{
		if (ft_strnstr(cmd_sp[x], "<", 1) ||
		ft_strnstr(cmd_sp[x], ">", 1) ||
		ft_strnstr(cmd_sp[x], ">>", 2))
			break ;
	}
	if (cmd_sp[x] == NULL)
	 	return (-1);
	return (x);
}

void 	take_redirec(char **aux_cmd, int i, char **cmd_sp)
{
	i = find_redirec(cmd_sp, -1);
	if (i != -1)
	{ 
		ft_printf("%s\n", cmd_sp[i]);
	}
	(void)*aux_cmd;
}