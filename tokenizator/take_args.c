/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:04:52 by vifernan          #+#    #+#             */
/*   Updated: 2022/12/15 17:43:49 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*aux_path_val(char *cmd, char *aux_cmd, char **path_sp, int i)
{
	char	*aux_path;
	
	aux_path = NULL;
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
			aux_path = NULL;
		}
	}
	return (aux_path);
}

char	*find_path(char *cmd, char *all_path, int i)
{
	char	*aux_cmd;
	char	*aux_path;
	char	**path_sp;

	aux_cmd = ft_strjoin("/", skip_quotes(cmd, -1));
	path_sp = ft_split(all_path, ':');
	aux_path = aux_path_val(cmd, aux_cmd, path_sp, i);
	free_matrix(path_sp);
	free(aux_cmd);
	return (aux_path);
}

void	take_args(char **cmd_sp, t_pipe *ret, char *all_path)
{
	ret->exec_path = find_path(cmd_sp[0], all_path, -1);
	ret->argv = cmd_sp;
	if (!ft_strcmp("cd", ret->argv[0]) || !ft_strcmp("echo", ret->argv[0]) || !ft_strcmp("pwd", ret->argv[0]))
	{
		free(ret->exec_path);
		ret->exec_path = NULL;
	}
}