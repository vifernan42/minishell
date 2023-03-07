/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:26:56 by ialvarez          #+#    #+#             */
/*   Updated: 2023/03/07 20:38:57 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envu, int fd)
{
	int	i;

	i = -1;
	if (envu)
	{
		while (envu[++i] != NULL)
		{
			if (ft_strchr(envu[i], '=') && envu[i][0] != '?')
				ft_putendl_fd(envu[i], fd);
		}
	}
	else
		ft_printf("minishell: env: not found\n");
	return (0);
}
