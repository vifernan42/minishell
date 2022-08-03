/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 19:08:11 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/16 13:07:17 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*a;
	const char		*b;

	a = dst;
	b = src;
	while (n--)
	{
		*a = *b;
		if ((unsigned char)*b == (unsigned char)c)
			return ((void *)++a);
		a++;
		b++;
	}
	return (NULL);
}
