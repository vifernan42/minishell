/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/15 20:52:31 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	do_echo(char *str, int fd)
{
	int		i;

	i = -1;
	while (str[++i] != '\0')
		write(fd, &str[i], 1);
}

static int	echo_flag(char **argv)
{
	int	i;
	int	u;

	i = 0;
	while (argv[++i] != NULL)
	{
		if (argv[i][0] == '-' && argv[i][1] == 'n')
		{
			u = 0;
			while (argv[i][++u] != '\0')
			{
				if (argv[i][u] != 'n')
					return (i);
			}
		}
		else
			return (i);
	}
	return (1);
}

int	my_echo(char **argv, int fd)
{
	int		flag;
	int		i;
	char	*prin;

	flag = echo_flag(argv);
	i = flag;
	while (argv[i] != NULL)
	{
		prin = skip_quotes(ft_strdup(argv[i]), 0);
		do_echo(prin, fd);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
		free(prin);
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}
