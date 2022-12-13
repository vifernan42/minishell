/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:44:49 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/13 19:34:08 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_update(t_data *data, char *new_line, char *key)
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
	new_env = (char **)malloc((j + 2) * sizeof(char *));
	i = -1;
	j = 0;
	while(data->env[++i] != NULL)
	{
		if (ft_strcmp(key, data->env[i]))
			new_env[j++] = ft_strdup(data->env[i]);
		free(data->env[i]);
	}
	new_env[j] = new_line;
	new_env[j + 1] = NULL;
	free(data->env);
	data->env = new_env;
}

char	*search_variable(char **env, char *key)
{
	int	i;

	i = -1;
	while(env[++i] != NULL)
	{
		if (!ft_strcmp(key, env[i]))
		{
			return(env[i] + ft_strlen(key));
			break ;
		}
	}
	return (NULL);
}

void	update_pwd(t_data *data, char *dir)
{
	int	i;

	i = -1;
	while(data->env[++i] != NULL)
	{
		if (!ft_strcmp("PWD=", data->env[i]))
		{
			free(data->env[i]);
			data->env[i] = dir;
			break ;
		}
	}
}


int	my_chdir(t_data *data, const char *path)
{
	char	*dir;
	char	*OLDPWD;

	dir = getcwd(NULL, 0);
	OLDPWD = NULL;
	if (!path)
		path = search_variable(data->env, "HOME=");
	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	if (!chdir(path))
	{
		OLDPWD = ft_strjoin("OLDPWD=", dir);
		if (path[0] != '.' && ft_strlen(path) == 1)
			env_update(data, OLDPWD, "OLDPWD=");
		dir = ft_strjoin("PWD=", getcwd(NULL, 0));
		update_pwd(data, dir);
		return (0);
	}
	ft_printf("minishell: cd: %s\n", path);
	return (1);
}