/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charindex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 06:29:41 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/14 20:02:36 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_charindex(char *str, char c)
{
	int	i;

	i = -1;
	if (!str || c == '\0')
		return (-1);
	while (str[++i] != '\0')
	{
		if (str[i] == c)
			return (i);
	}
	return (-1);
}
