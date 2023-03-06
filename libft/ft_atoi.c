/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talentum <talentum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 20:11:04 by ialvarez          #+#    #+#             */
/*   Updated: 2023/03/05 20:41:22 by talentum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_max_min(unsigned long long num, int p)
{
	if (num > 9223372036854775807 && p > 0)
		return (-1);
	if (num - 1 > 9223372036854775807 && p < 0)
		return (0);
	return (num * p);
}

int	ft_atoi(const char *str)
{
	int					i;
	int					p;
	unsigned long long	num;

	i = 0;
	p = 1;
	num = 0;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			p = p * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	return (check_max_min(num, p));
}
