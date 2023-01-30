/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:25:06 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/30 18:57:30 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*skip_result(char *str, char c, int count, int k)
{
	char	*s;
	int		j;
	int		i;

	if (!str)
		return(NULL);
	s = malloc(sizeof(char) * (int)ft_strlen(str) - count + 1);
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != c)
			s[j++] = str[i];
	}
	s[j] = '\0';
	return (skip_quotes(s, k));
}

char	*skip_quotes(char *str, int i)
{
	int		count;
	char	c;
	char	*aux;

	count = 0;
	c = 0;
	aux = NULL;
	while (str[++i] != '\0')
	{
		if ((str[i] == '\'' || str[i] == '\"') && ((c == 0)
				|| (count > 0 && (count % 2 == 0))))
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
			count++;
		}
		else if ((c == '\'' || c == '\"') && str[i] == c)
		{
			count++;
			break ;
		}
	}
	if (count % 2 == 0 && count > 0)
	{
		aux = str;
		free(str);
		str = skip_result(str, c, count, i);
	}
	else if (aux)
		free(aux);
	return (str);
}
