/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:27:00 by ialvarez          #+#    #+#             */
/*   Updated: 2022/11/30 17:52:55 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwdcurrent(t_pipe *list)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!pwd)
	{
		write(1, "entra\n", 6);
		return (-1);
	}
	write(list->out_fd, pwd, ft_strlen(pwd));
	write(list->out_fd, "\n", 1);
	free(pwd);
	return (1);
}
