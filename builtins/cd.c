/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:44:49 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/13 16:54:13 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	env_(t_data

int	my_chdir(t_data *data, const char *path)
{
	char	*dir;

	data = NULL;
	path = NULL;
	dir = getenv("PWD");
	printf("esto es path: %s\n", dir);
	return (0);
	
}

