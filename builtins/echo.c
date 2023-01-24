/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/24 20:02:01 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"




void	do_echo(char *str, int fd)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		write(fd, &str[i], 1);
}

int my_echo(char **argv, int fd)
{
	int flag;
	int i;
	int u;

	flag = 1;
	i = 1;
	u = 0;

	while(argv[++u] != '\0')
	{
		if (!ft_strcmp("-n",argv[1]))
			if (!ft_strcmp("-n",argv[u]))
			{
				flag = 0;
				i++;
			}
	}
	while (argv[i] != NULL)
	{
		do_echo(argv[i], fd);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}