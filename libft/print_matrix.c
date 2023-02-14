/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 19:37:25 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/14 18:49:38 by vifernan         ###   ########.fr       */
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
			write(1, &matrix[i][j], 1);
		write(1, "\n", 1);
	}
}
