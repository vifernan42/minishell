/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 15:26:29 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/16 18:23:43 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*a;
	const unsigned char	*b;
	unsigned char		*keepa;
	const unsigned char	*keepb;

	a = dst;
	b = src;
	if (!src && !dst)
		return (NULL);
	if (a < b)
	{
		while (len--)
			*a++ = *b++;
	}
	else if (a > b)
	{
		keepa = a + (len - 1);
		keepb = b + (len - 1);
		while (len--)
			*keepa-- = *keepb--;
	}
	return (dst);
}
