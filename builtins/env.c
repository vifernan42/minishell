/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:26:56 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/15 17:28:07 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(char **envu, int fd)
{
	int	i;

	i = -1;
	while (envu[++i] != NULL)
	{
		if (ft_strchr(envu[i], '=') && envu[i][0] != '?')
			ft_putendl_fd(envu[i], fd);
	}
	return (0);
}
