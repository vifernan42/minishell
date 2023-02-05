/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:44:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/26 20:36:24 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*change_two_dots(char *path)
{
	int	i;
	int	index;
	char	*aux;

	i = -1;
	if (path && (int)ft_strlen(path) > 0)
	{
		while (path[++i] != '\0')
		{
			if (path[i] == '/')
				index = i;
		}
		aux = (char *)malloc(sizeof(char) * index + 1);
		i = -1;
		while (path[++i] != '\0')
		{
			if (i < index)
				aux[i] = path[i];
		}
		aux[index] = '\0';
		return (aux);
	}
	/*else*/
	return (NULL);
}

int	my_chdir(t_data *data, char *path)
{
	char	*dir;

	if (path[0] == '~')
	{
		dir = ft_strjoin(search_variable(data->env, "HOME="), path + 1); /*leaks?*/
		path = dir;
		free(dir);
	}
	dir = search_variable(data->env, "PWD=");
	if (!path)
		path = search_variable(data->env, "HOME=");
	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n"); /*guardar el home*/
		return (1);
	}
	if (!ft_strcmp_built(path, ".."))
	{
		path =  change_two_dots(search_variable(data->env, "PWD="));
		if (!chdir(path))
		{
			data->oldpwd = ft_strjoin("OLDPWD=", dir);
			if (path[0] != '.' && ft_strlen(path) == 1)
				env_update(data, data->oldpwd, "OLDPWD=");
			dir = ft_strjoin("PWD=", getcwd(NULL, 0));
			update_env_var(data, dir, "PWD=");
			return (0);
		}
		ft_printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		env_update(data, ft_strjoin("PWD=", path), "PWD=");
	}
	else
	{
		if (!chdir(path))
		{
			data->oldpwd = ft_strjoin("OLDPWD=", dir);
			if (path[0] != '.' && ft_strlen(path) == 1)
				env_update(data, data->oldpwd, "OLDPWD=");
			dir = ft_strjoin("PWD=", getcwd(NULL, 0));
			update_env_var(data, dir, "PWD=");
			return (0);
		}
		if (!ft_strcmp_built(path, ".."))
		{
			ft_printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			dir = change_two_dots(search_variable(data->env, "PWD="));
			update_env_var(data, dir, "PWD=");
		}
		else
			ft_printf("minishell: cd: %s\n", path);
	}
	return (1);
}