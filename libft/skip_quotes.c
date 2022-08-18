/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 16:25:06 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/18 17:38:49 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*skip_quotes(char *str)
{
	int		i;
	int		count;
	char	c;

	i = -1;
	count = 0;
	c = 0;
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
	return (str);
}
