/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 15:49:13 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/20 16:15:53 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	j;
	char			*dst;

	j = 0;
	if (!s)
		return (NULL);
	dst = (char *)malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!dst)
		return (NULL);
	while (s[j])
	{
		dst[j] = f(j, s[j]);
		j++;
	}
	dst[j] = '\0';
	return (dst);
}
