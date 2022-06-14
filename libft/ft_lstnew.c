/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:26:50 by ialvarez          #+#    #+#             */
/*   Updated: 2021/04/20 20:35:27 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*other;

	other = malloc(sizeof(t_list));
	if (!other)
		return (NULL);
	other->content = content;
	other->next = NULL;
	return (other);
}
