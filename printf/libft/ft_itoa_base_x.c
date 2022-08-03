/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:50:28 by ialvarez          #+#    #+#             */
/*   Updated: 2021/09/13 17:03:05 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static	int	ft_size(unsigned long n, int dh)
{
	int	c;

	c = 0;
	if (n <= 0)
		c++;
	while (n != 0)
	{
		c++;
		n = n / dh;
	}
	return (c);
}

char	*ft_itoa_base_x(unsigned long n, int dh)
{
	int		len;
	char	*num;
	char	*base;

	base = "0123456789ABCDEF";
	len = ft_size(n, dh);
	num = (char *)malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (n < 0)
	{
		num[0] = '-';
		n = n * -1;
	}
	if (n == 0)
		num[0] = '0';
	while (n != 0)
	{
		len--;
		num[len] = base[n % dh];
		n = n / dh;
	}
	return (num);
}
