/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 20:31:34 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/08 20:33:50 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ret_key(char *str, int i, int j, char c)
{
	int		lock;
	char	*ret;

	lock = 0;
	ret = malloc(sizeof(char) * j + 1);
	j = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && lock == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == 0 && lock == 0)
			&& ++lock)
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
		}
		else if ((c == '\'' || c == '\"') && str[i] == c && lock == 1 && lock--)
			c = 0;
		else if ((str[i] != '\'' && str[i] != '\"') || lock == 1)
			ret[j++] = str[i];
	}
	ret[j] = '\0';
	return (ret);
}

char	*find_key(char *str, int i, int j)
{
	char	c;
	int		lock;

	c = '\0';
	lock = 0;
	while (str[++i] != '\0')
	{
		if ((str[i] == '<' || str[i] == '>') && lock == 0)
			break ;
		if ((str[i] == '\'' || str[i] == '\"') && (c == 0 && lock == 0)
			&& ++lock)
		{
			if (str[i] == '\'')
				c = '\'';
			else
				c = '\"';
		}
		else if ((c == '\'' || c == '\"') && str[i] == c && lock == 1 && lock--)
			c = 0;
		else if ((str[i] != '\'' && str[i] != '\"') || lock == 1)
			j++;
	}
	return (ret_key(str, -1, j, '\0'));
}
