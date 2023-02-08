/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:27:00 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/08 21:03:13 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwdcurrent(t_pipe *list, t_data *data)
{
	char	*pwd;
	int		i;

	i = -1;
	pwd = NULL;
	pwd = search_variable(data->env, "PWD=");
	if (!pwd)
	{
		if (!data->oldpwd)
			write(list->out_fd, "", 0);
		else
		{
			while (data->oldpwd[++i] != '\0')
			{
				if (data->oldpwd[i] == '=')
					while (data->oldpwd[++i] != '\0')
						write(list->out_fd, &data->oldpwd[i], 1);
			}
		}
		write(list->out_fd, "\n", 1);
		return (-1);
	}
	write(list->out_fd, pwd, ft_strlen(pwd));
	write(list->out_fd, "\n", 1);
	return (1);
}
