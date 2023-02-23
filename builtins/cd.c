/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:44:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/23 20:16:36 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*change_two_dots(char *path)
{
	int		i;
	int		index;
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
	return (NULL);
}

static int	cd_no_path(t_data *data, char *aux, char *path, char *dir)
{
	data->oldpwd = ft_strjoin("OLDPWD=", dir);
	if (path[0] != '.' && ft_strlen(path) == 1)
		env_update(data, ft_strdup(data->oldpwd), "OLDPWD=");
	free(data->oldpwd);
	aux = getcwd(NULL, 0);
	dir = ft_strjoin("PWD=", aux);
	free(aux);
	update_env_var(data, dir, "PWD=");
	free(path);
	return (0);
}

static int	do_my_chdir(t_data *data, char *aux, char *path, char *dir)
{
	if (!ft_strcmp_built(path, ".."))
	{
		free(path);
		path = change_two_dots(search_variable(data->env, "PWD="));
		if (!chdir(path))
			return (cd_no_path(data, aux, path, dir));
		ft_printf("cd: error retrieving current directory: getcwd: \
				cannot access parent directories: No such file or directory\n");
		env_update(data, ft_strjoin("PWD=", path), "PWD=");
	}
	else
	{
		if (!chdir(path))
			return (cd_no_path(data, aux, path, dir));
		if (!ft_strcmp_built(path, ".."))
		{
			ft_printf("cd: error retrieving current directory: getcwd: \
				cannot access parent directories: No such file or directory\n");
			dir = change_two_dots(search_variable(data->env, "PWD="));
			update_env_var(data, dir, "PWD=");
		}
		else
			ft_printf("minishell: cd: %s\n", path);
	}
	free(path);
	return (1);
}

int	my_chdir(t_data *data, char *path)
{
	char	*dir;
	char	*aux;

	aux = NULL;
	if (path && path[0] == '~')
	{
		dir = ft_strjoin(search_variable(data->env, "HOME="), path + 1);
		free(path);
		path = ft_strdup(dir);
		free(dir);
	}
	dir = search_variable(data->env, "PWD=");
	if (!path)
		path = ft_strdup(search_variable(data->env, "HOME="));
	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n");
		return (1);
	}
	return (do_my_chdir(data, aux, path, dir));
}
