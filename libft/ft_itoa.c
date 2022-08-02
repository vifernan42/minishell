/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 19:50:28 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/20 13:59:39 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_size(int n)
{
	int	c;

	c = 0;
	if (n <= 0)
		c++;
	while (n != 0)
	{
		c++;
		n = n / 10;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	int		len;
	long	pus;
	char	*num;

	len = ft_size(n);
	pus = n;
	num = (char *)malloc((len + 1) * sizeof(char));
	if (!num)
		return (NULL);
	num[len] = '\0';
	if (pus < 0)
	{
		num[0] = '-';
		pus = pus * -1;
	}
	if (pus == 0)
		num[0] = '0';
	while (pus != 0)
	{
		len--;
		num[len] = (pus % 10) + '0';
		pus = pus / 10;
	}
	return (num);
}
