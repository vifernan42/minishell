/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 18:15:00 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/11 15:37:19 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		a;
	int		len;
	char	x;

	x = c;
	a = 0;
	len = ft_strlen(s);
	while (a < len + 1)
	{
		if (s[a] == x)
			return ((char *)s + a);
		a++;
	}
	return (NULL);
}
