/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 20:00:55 by ialvarez          #+#    #+#             */
/*   Updated: 2021/09/14 18:25:49 by ialvarez         ###   ########.fr       */
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
/*
int main ()
{
  // int r = 0;
  // int i = -555;
   size_t j = 16;
   //char *c = "cach";
   int ret = 0;
   //ret  = ft__printf("%dhola%d%d%s-->%cALON",r,i,j,x,c);
   ret  = ft_printf("%p\n", (void *)&j);
   int p = printf("%p\n", (void *)&j);
   printf("%d %d\n", ret, p);
 //  system("leaks a.out");
}*/
