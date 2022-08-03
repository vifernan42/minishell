/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:25:06 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/02 20:25:22 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*skip_result(char *str, char c, int count)
{
	char	*s;
	int		j;
	int		i;

	s = malloc(sizeof(char) * ft_strlen(str) - count + 1);
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != c)
			s[j++] = str[i];
	}
	s[j] = '\0';
	free(str);
	return (skip_quotes(s));
}

char	*skip_quotes2(char *str)
{
	int		i;
	char	c;
	int		count;

	if (!str)
		return (NULL);
	i = -1;
	c = 0;
	count = 0;
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
			count++;
	}
	return (skip_result(str, c, count));
}

char	*skip_quotes(char *str)
{
	int		i;
	int		count;
	char	*aux;
	char	c;

	i = -1;
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
			count++;
	}
	if (count % 2 == 0 && count > 0)
	{
		aux = strdup(str);
		free(str);
		str = skip_quotes2(aux);
		free(aux);
	}
	else
		free(aux);
	return (str);
}