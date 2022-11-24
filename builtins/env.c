/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 16:26:56 by ialvarez          #+#    #+#             */
/*   Updated: 2022/11/23 16:56:01 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env(char **envu, int fd)
{
	int	i;

	i = -1;
	while (envu[++i] != NULL)
	{
		if (ft_strchr(envu[i], '='))
			ft_putendl_fd(envu[i], fd);
	}
	return (0);
}