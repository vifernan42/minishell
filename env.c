/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:09:52 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/09 13:56:13 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**keep_env(char **env)
{
	char	**envir;
	int		i;
	int		j;

	i = 0;
	while(env[i] != NULL)
		i++;
	envir = (char **)malloc((i + 1) * sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		envir[i] = (char *)malloc((ft_strlen(envir[i]) + 1) * sizeof(char));
		while (env[i][j])
		{
			envir[i][j] = env[i][j];
			j++;
		}
		envir[i][j] = '\0';
		i++;
	}
	envir[i] = NULL;
	return (envir);
}
