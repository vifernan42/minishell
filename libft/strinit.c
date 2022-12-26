/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:48:05 by vifernan          #+#    #+#             */
/*   Updated: 2022/12/23 06:28:38 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strinit(char *str, char x)
{
	int		i;
	char	*aux;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == x)
			break ;
	}
	aux = malloc(sizeof(char *) * i + 1);
	i = -1;
	while (str[++i] != '\0')
	{
		aux[i] = str[i];
		if (str[i] == x)
			break ;
	}
	aux[i] = '\0';
	return (aux);
}
