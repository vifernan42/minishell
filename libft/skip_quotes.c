/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:25:06 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/09 19:47:13 by ialvarez         ###   ########.fr       */
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
		return (NULL);
	s = malloc(sizeof(char) * (int)ft_strlen(str) - count + 1);
	i = -1;
	j = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] != c && count > 0) || (str[i] && count == 0))
		{
			s[j++] = str[i];
		}
		else if (str[i] == c)
			count--;
	}
	s[j] = '\0';
	return (skip_quotes(s, k));
}

/*static void	aux_quotes(char *str, int *i, int *count, char *c)
{
		if (str[*i] == '\'')
			*c = '\'';
		else
			*c = '\"';
		(*count)++;
}*/

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
			//aux_quotes(str, &i, &count, &c);
			if (str[i] == '\'') /*mirar esto*/ 
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
	printf("str: $%s$\ncount: $%d$\n\n", str, count);
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
