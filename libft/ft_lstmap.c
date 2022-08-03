/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 20:40:49 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/21 21:32:04 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dst;
	t_list	*begin;

	if (lst && f)
	{
		dst = ft_lstnew(f(lst->content));
		begin = dst;
		lst = lst->next;
		while (lst)
		{
			dst->next = ft_lstnew(f(lst->content));
			if (!dst)
				del(lst);
			dst = dst->next;
			lst = lst->next;
		}
		return (begin);
	}
	return (NULL);
}

