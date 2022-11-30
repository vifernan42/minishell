/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2022/11/30 17:44:32 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echos(char **argv, int fd)
{
	int flag;
	int i;

	flag = 0;
	i = 1;
	if (ft_strcmp(argv[1], "-n"))
		flag = 1;
	i = 1;
	while (argv[i] != NULL)
	{
		if (flag != 1)
			i++;
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}