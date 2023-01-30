/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/27 19:10:51 by vifernan         ###   ########.fr       */
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

int	check_flag(char **argv)
{
	int	i;
	int	u;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'n')
		{
			u = 0;
			while(argv[i][++u] != '\0')
			{
				if (argv[i][u] != 'n')
					return(i);
			}
		}
		else
			return (i);
	}
	return (1);
}

int my_echo(char **argv, int fd)
{
	int flag;
	int i;

	flag = check_flag(argv);
	i = flag;
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