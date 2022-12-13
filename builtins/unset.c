/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 20:03:33 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/13 20:11:59 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	my_unset(t_data *data, char *key)
{
	int 	i;
	int 	j;
	char	**new_env;

	i = -1;
	j = 0;
	while(data->env[++i] != NULL)
	{
		if (ft_strcmp(key, data->env[i]))
			j++;
	}
	if (j == i)
		return ;
	new_env = (char **)malloc((j + 1) * sizeof(char *));
	i = -1;
	j = 0;
	while(data->env[++i] != NULL)
	{
		if (ft_strcmp(key, data->env[i]))
			new_env[j++] = ft_strdup(data->env[i]);
		free(data->env[i]);
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
}