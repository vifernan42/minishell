/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keep_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:09:52 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/14 19:43:42 by vifernan         ###   ########.fr       */
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
	i = -1;
	while (env[++i] != NULL)
	{
		j = -1;
		envir[i] = (char *)malloc((int)ft_strlen(env[i]) + 1 * sizeof(char));
		while (env[i][++j] != '\0')
			envir[i][j] = env[i][j];
		envir[i][j] = '\0';
	}
	envir[i] = NULL;
	return (envir);
}
