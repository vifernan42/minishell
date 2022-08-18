/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:00:55 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/18 19:41:33 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	a_list;
	t_flags	*fl;
	int		x;

	fl = ft_calloc(1, sizeof(t_flags));
	if (!fl)
		return (-1);
	va_start(a_list, format);
	ft_vsprintf(format, a_list, fl);
	x = fl->ret;
	free(fl);
	va_end(a_list);
	return (x);
}
