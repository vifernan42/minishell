/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:58:18 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/16 13:22:45 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	z;
	size_t	upto;

	if (!s)
		return (NULL);
	z = ft_strlen(s);
	if (start >= z)
	{
		dst = malloc(1);
		dst[0] = '\0';
		return (dst);
	}
	if ((start + len) > z)
		upto = z - start;
	else
		upto = len;
	dst = malloc(sizeof (char) * (upto) + 1);
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s + start, upto);
	dst[upto] = '\0';
	return (dst);
}
