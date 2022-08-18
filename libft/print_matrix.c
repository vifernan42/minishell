/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:37:25 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/18 19:39:22 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_matrix(char **matrix)
{
	int		i;
	int		j;

	i = -1;
	while (matrix[++i] != NULL)
	{
		j = -1;
		while (matrix[i][++j] != '\0')
			printf("%c", matrix[i][j]);		
		printf("\n");
	}
}