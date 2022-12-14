/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/14 17:47:18 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int my_echo(t_data *data, char **argv, int fd)
{
	int flag;
	int i;

	flag = 0;
	i = 1;
	if (ft_strcmp(argv[1], "-n"))
		flag = 1;
	i = 1;
	if (flag != 1)
		i++;
	while (argv[i] != NULL)
	{
		if (argv[i][0] == '$')
		{
			//ft_putstr_fd(argv[i], fd);
			ft_putstr_fd(search_variable(data->env, argv[i] + 1) + 1, fd);
		}
		else
			ft_putstr_fd(argv[i], fd);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}