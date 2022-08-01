/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 17:43:52 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/28 18:54:15 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	int		i;

	if (!s1)
		return (NULL);
	i = ft_strlen(s1);
	dst = malloc(sizeof (char) * (i + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, s1, i);
	dst[i] = '\0';
	return (dst);
}
