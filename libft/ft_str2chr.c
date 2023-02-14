/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str2chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 18:08:01 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/14 20:02:23 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str2chr(const char *s, int c)
{
	int		a;
	int		len;
	int		count;

	a = 0;
	count = 0;
	len = ft_strlen(s);
	while (a < len + 1)
	{
		if (s[a] == (char)c)
		{
			if (s[a + 1] != (char)c)
				count++;
			if (count == 2)
				return ((char *)s + a);
		}
		a++;
	}
	return (NULL);
}
