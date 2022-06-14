/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:01:20 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/20 15:48:23 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_cachopo(char **dst, char const *init, char c)
{
	int			i;
	char const	*start;

	i = 0;
	while (*init)
	{
		if (*init != c)
		{
			start = init;
			while (*init != c && *init)
				init++;
			dst[i++] = ft_substr(start, 0, init - start);
		}
		else
			init++;
	}
	dst[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	int			i;
	char		**dst;
	char const	*init;

	init = s;
	i = 0;
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s != c && *s)
				s++;
		}
		if (*s)
			s++;
	}
	dst = (char **)malloc((i + 1) * sizeof(char *));
	if (!dst)
		return (NULL);
	ft_cachopo(dst, init, c);
	return (dst);
}
