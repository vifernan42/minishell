/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strinkey.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 19:00:28 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/14 20:02:06 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strinkey(const char *str, const char *key)
{
	int	i;
	int	j;

	i = -1;
	if (key == NULL || str == NULL)
		return (-1);
	while (str[++i] != '\0')
	{
		j = -1;
		while (key[++j] != '\0')
		{
			if (str[i] == key[j])
				return (i);
		}
	}
	return (-1);
}
