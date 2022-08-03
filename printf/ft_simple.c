/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 19:14:45 by ialvarez          #+#    #+#             */
/*   Updated: 2021/09/14 18:29:14 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_dec(const char *format, va_list a_list, t_flags *fl)
{
	if (format[fl->o] == 'd' || format[fl->o] == 'i')
	{
		fl->some = ft_itoa(va_arg(a_list, int));
		fl->str = fl->some;
	}
	else if (format[fl->o] == 'u')
	{
		fl->some = ft_itoa_base((unsigned int)va_arg(a_list, int), 10);
		fl->str = fl->some;
	}
}

static void	ft_specifier_triple(const char *format, va_list a_list, t_flags *fl)
{
	int	i;
	int	j;

	i = 0;
	j = 2;
	if (format[fl->o] == 'X')
		fl->str = ft_itoa_base_x((unsigned int)va_arg(a_list, void *), 16);
	else if (format[fl->o] == 'x')
		fl->str = ft_itoa_base((unsigned int)va_arg(a_list, void *), 16);
	else if (format[fl->o] == 'p')
	{
		fl->some = ft_itoa_base((unsigned long long)va_arg(a_list, void *), 16);
		fl->str = ft_strjoin("0x", fl->some);
		free(fl->some);
	}
}

static void	ft_putstr_fda(char *s, int fd, t_flags *fl)
{
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	fl->ret = fl->ret + ft_strlen(s);
}

char	*ft_simple(const char *format, va_list a_list, t_flags *fl)
{
	char	c;

	if (format[fl->o] == 'c')
	{
		c = va_arg(a_list, int);
		fl->ret += write(1, &c, 1);
	}
	else if (format[fl->o] == 'u' || format[fl->o] == 'd'
		|| format[fl->o] == 'i')
		ft_dec(format, a_list, fl);
	else if (format[fl->o] == 's')
	{
		fl->str = va_arg(a_list, char *);
		if (fl->str == NULL)
			fl->str = "(null)";
	}
	else if (format[fl->o] == '%')
		fl->str = ft_char2str(format[fl->o]);
	else if (format[fl->o] == 'X' || format[fl->o] == 'x'
		|| format[fl->o] == 'p')
		ft_specifier_triple(format, a_list, fl);
	if (format[fl->o] != 'c')
		ft_putstr_fda(fl->str, 1, fl);
	return (fl->str);
}
