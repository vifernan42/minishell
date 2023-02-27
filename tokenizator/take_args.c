/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 13:04:52 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/27 21:42:33 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_aux(char **aux_path)
{
	free(*aux_path);
	*aux_path = NULL;
}

static char	*aux_path_val(char *cmd, char *aux_cmd, char **path_sp, int i)
{
	char	*aux_path;

	aux_path = NULL;
	if ((cmd[0] != '/') && (cmd[0] != '.' && cmd[1] != '/')
		&& (cmd[0] != '.' && cmd[1] != '.' && cmd[2] != '/'))
	{
		while (path_sp[++i] != NULL)
		{
			aux_path = ft_strjoin(path_sp[i], aux_cmd);
			if (access(aux_path, F_OK) == 0)
				break ;
			free_aux(&aux_path);
		}
	}
	else
		aux_path = ft_strdup(cmd);
	return (aux_path);
}

static char	*find_path(char *cmd, char *all_path, int i)
{
	char	*aux_cmd;
	char	*aux_path;
	char	**path_sp;

	if (!all_path)
		return (NULL);
	aux_cmd = ft_strjoin("/", skip_quotes(cmd, 0));
	path_sp = ft_split(all_path, ':');
	aux_path = aux_path_val(cmd, aux_cmd, path_sp, i);
	free_matrix(path_sp);
	free(aux_cmd);
	return (aux_path);
}

char	*take_args(char **cmd_sp, t_pipe *ret, char *all_path)
{
	char	*path;

	path = find_path(cmd_sp[0], all_path, -1);
	ret->argv = cmd_sp;
	if (!ft_strcmp("cd", ret->argv[0]) || !ft_strcmp("echo", ret->argv[0])
		|| !ft_strcmp("pwd", ret->argv[0]) || !ft_strcmp("env", ret->argv[0])
		|| !ft_strcmp("ENV", ret->argv[0]))
	{
		free(path);
		path = NULL;
	}
	return (path);
}
