/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/21 19:11:37 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/21 20:13:58 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tur;

	if (lst)
	{
		while (*lst)
		{
			tur = (*lst)->next;
			ft_lstdelone(*lst, del);
			*lst = tur;
		}
	}
}
