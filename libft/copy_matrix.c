/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 19:49:58 by vifernan          #+#    #+#             */
/*   Updated: 2022/07/26 20:06:42 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**copy_matrix(char **matrix)
{
	char	**dst;
	int		i;

	if (!matrix)
		return (NULL);
	i = 0;
	while(matrix[i] != NULL)
		i++;
	dst = malloc(sizeof(char **) * i + 1);
	i = 0;
	while(matrix[i] != NULL)
	{
		dst[i] = ft_strdup(matrix[i]);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}
