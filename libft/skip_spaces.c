/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:05:32 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/11 19:23:24 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*sk_front(char *str)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	j = ft_strlen(str);
	if (str[j] == 0)
		return (str);
	while (j > 0)
	{
		if (str[j] == ' ' )
		{
			j--;
			i++;
		}
		else	
			break ;
	}
	aux = ft_substr(str, 0, ft_strlen(str) - i);
	free(str);
	return (aux);
}

char	*skip_spaces(char *str)
{
	int		i;
	char	*aux;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ')
		i++;
	aux =  ft_substr(str, i, ft_strlen(str) - i);
	return (sk_front(aux));
}