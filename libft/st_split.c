/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:01:20 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/20 21:22:08 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	check_quotes(char const *s, char c, int i)
{
	int		j;

	j = i;
	while (s[++j] != '\0')
	{
		if (s[j] == c)
			return (j + 1);
	}
	return (i + 1);
}

static	int	aux_split(char const *s, int i, char c)
{
	char	x;

	x = 0;
	if (s[i] == '\"' || s[i] == '\'')
	{
		if (s[i] == '\"')
			x = '\"';
		else
			x = '\'';
		i = check_quotes(s, x, i);
	}
	while (s[i] != c && s[i] != '\'' \
		&& s[i] != '\"' && s[i] != '\0')
		i++;
	return (i);
}

char	**ft_cacho(char **dst, char const *init, char c)
{
	int			i;
	int			j;
	int			z;

	i = 0;
	z = 0;
	while (i < (int)ft_strlen(init))
	{
		if (i == 0 || init[i - 1] == c)
			j = i;
		i = aux_split(init, i, c);
		if (init[i] == c || i == (int)ft_strlen(init))
		{
			if ((i - j) == 0)
				dst[z++] = ft_strdup("\0");
			else
				dst[z++] = ft_substr(init, j, i - j);
		}
		if ((init[i] != '\'' && init[i] != '\"') \
				&& i != (int)ft_strlen(init))
			i++;
	}
	dst[z] = NULL;
	return (dst);
}

char	**st_split(char const *s, char c)
{
	int			i;
	int			count;
	char		**dst;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	while (i < (int)ft_strlen(s))
	{
		i = aux_split(s, i, c);
		if (s[i] == c)
			count++;
		if (s[i] != '\'' && s[i] != '\"')
			i++;
	}
	dst = (char **)malloc((count + 2) * sizeof(char *));
	if (!dst)
		return (NULL);
	return (ft_cacho(dst, s, c));
}
