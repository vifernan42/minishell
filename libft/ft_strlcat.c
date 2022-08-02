/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:00:06 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/18 19:10:47 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	a = ft_strlen(dst);
	if (a > dstsize)
		return (dstsize + ft_strlen(src));
	while (a + 1 < dstsize && *src)
		dst[a++] = *src++;
	dst[a] = '\0';
	while (*src++)
		a++;
	return (a);
}
