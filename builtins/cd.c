/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:44:49 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/20 19:14:54 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	my_chdir(t_data *data, const char *path)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (!path)
		path = search_variable(data->env, "HOME=");
	if (!path)
	{
		ft_printf("minishell: cd: HOME not set\n"); /*guardar el home*/
		return (1);
	}
	if (!chdir(path))
	{
		data->oldpwd = ft_strjoin("OLDPWD=", dir);
		if (path[0] != '.' && ft_strlen(path) == 1)
			env_update(data, data->oldpwd, "OLDPWD=");
		dir = ft_strjoin("PWD=", getcwd(NULL, 0));
		update_env_var(data, dir, "PWD=");
		return (0);
	}
	ft_printf("minishell: cd: %s\n", path);
	return (1);
}