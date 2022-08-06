/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 15:57:19 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/05 16:00:29 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr2(const char *s, int c)
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
			return ((char *)s + a + 2);
		a++;
	}
	return (NULL);
}