/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:50:51 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/16 13:21:28 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	x;

	x = c;
	len = ft_strlen(s);
	while (len + 1 > 0)
	{
		if (s[len] == x)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}
