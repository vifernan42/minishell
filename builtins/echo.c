/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2022/06/13 20:27:41 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int echos(char **argv, int fd)
{
	int flag;
	int i;

	flag = 0;
	i = 1;
	while (argv[i] && ft_strncmp(argv[i++], "-n", 2))
		flag = 1;
	i = 1;
	while (argv[i] != NULL)
	{
		ft_putstr_fd(argv[i], fd);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}
/*
int main(int argc, char **argv)
{
	int i = 0;
	(void)argc;
	i = echos(argv, 1);
}*/
