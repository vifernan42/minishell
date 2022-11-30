/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 19:26:51 by ialvarez          #+#    #+#             */
/*   Updated: 2022/11/29 14:49:36 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		id_valid(char *aux)
{
	int	i;

	i = -1;
	while (str[++i] != NULL)
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_' && str[i] != '=')
			return(0);		
	}
	return(1);
}

int		export(t_data *data, char **argv)
{
	
}