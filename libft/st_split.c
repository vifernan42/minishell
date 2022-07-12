/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:01:20 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/12 13:52:28 by vifernan         ###   ########.fr       */
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
		if (init[i] == '\"')
			i = check_quotes(init, '\"', i);
		while (init[i] != c && init[i] != '\"' && init[i] != '\0')
			i++;
		if (init[i] == c || i == (int)ft_strlen(init))
			dst[z++] = ft_substr(init, j, i - j);
		if (init[i] != '\"' && i != (int)ft_strlen(init))
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
		if (s[i] == '\"')
			i = check_quotes(s, '\"', i);
		if (s[i] != c)
			while (s[i] != c && s[i] != '\"' && s[i] != '\0')
				i++;
		if (s[i] == c)
			count++;
		if (s[i] != '\"')
			i++;
	}
	dst = (char **)malloc((count + 2) * sizeof(char *));
	if (!dst)
		return (NULL);
	return (ft_cacho(dst, s, c));
}
/*
int main()
{
	int		i;
	char	**str;

	//str = st_split("echo hola \"|\" | hola | ls -la$\"|\"", '|');
	str = st_split("uno \"|\"  | dos -\"|\"| tres\"|\"", '|');
	i = -1;
	while (str[++i] != NULL)
		printf("%s\n", str[i]);
}*/
