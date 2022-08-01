/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:37:30 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/16 13:31:12 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{	
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	dst = malloc(sizeof (char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (dst)
	{
		ft_memcpy(dst, s1, ft_strlen(s1));
		ft_memcpy(dst + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	}
	return (dst);
}
