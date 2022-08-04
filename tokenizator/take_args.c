/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:04:52 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/04 17:36:59 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char *all_path, int i)
{
	char	*aux_cmd;
	char	*aux_path;
	char	**path_sp;

	aux_cmd = ft_strjoin("/", cmd);
	aux_path = NULL;
	path_sp = ft_split(all_path, ':');
	if (cmd[0] == '/')
	{
		if (access(cmd, F_OK) == 0)
			aux_path = ft_strdup(cmd);
	}
	else
	{
		while (path_sp[++i] != NULL)
		{
			aux_path = ft_strjoin(path_sp[i], aux_cmd);
			if (access(aux_path, F_OK) == 0)
				break ;
			free(aux_path);
		}
	}
	free_matrix(path_sp);
	free(aux_cmd);
	return (aux_path);
}

void	take_args(char **cmd_sp, t_pipe *ret, char *all_path)
{
	ret->exec_path = find_path(cmd_sp[0], all_path, -1);
	if (ret->exec_path)
		ret->argv = cmd_sp;
}