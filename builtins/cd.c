/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:44:49 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/14 16:46:15 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		update_env_var(data, dir, "PWD=");
		return (0);
	}
	ft_printf("minishell: cd: %s\n", path);
	return (1);
}