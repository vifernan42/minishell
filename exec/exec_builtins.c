/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:51:00 by vifernan          #+#    #+#             */
/*   Updated: 2023/03/13 16:48:49 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_splitted(t_pipe *list, t_data *data)
{
	if (!list->argv[1])
		env(data->env, list->out_fd);
	else
		ft_printf("env: %s: No such file or directory\n", list->argv[1]);
}

int	exec_killers_builtins(t_pipe *list, t_data *data, int *pipe_fd)
{
	if (list->exec_path)
		return (0);
	if (!ft_strcmp_built(list->argv[0], "echo"))
		my_echo(list->argv, list->out_fd);
	else if (!ft_strcmp_built(list->argv[0], "pwd"))
		pwdcurrent(list, data);
	else if (!ft_strcmp_built(list->argv[0], "env")
		|| !ft_strcmp_built(list->argv[0], "ENV"))
		env_splitted(list, data);
	else
	{
		g_err_no = 127;
		ft_printf("minishell: %s: command not found\n", list->argv[0]);
	}
	if (list->out_fd != 1)
	{
		dup2(list->out_fd, STDOUT_FILENO);
		close(list->out_fd);
	}
	else if (list->next && list->out_fd)
		dup2(pipe_fd[WR_END], STDOUT_FILENO);
	close(pipe_fd[WR_END]);
	close(pipe_fd[RD_END]);
	exit (0);
	return (1);
}

int	exec_builtins(t_pipe *list, t_data *data)
{
	if (!list->argv || list->exec_path
		|| !ft_strcmp_built(list->argv[0], "pwd")
		|| !ft_strcmp_built(list->argv[0], "env")
		|| !ft_strcmp_built(list->argv[0], "ENV")
		|| !ft_strcmp_built(list->argv[0], "echo"))
		return (0);
	if (!ft_strcmp_built(list->argv[0], "exit"))
		my_exit(list->argv, data);
	else if (!ft_strcmp_built(list->argv[0], "cd"))
		my_chdir(data, ft_strdup(list->argv[1]));
	else if (!ft_strcmp_built(list->argv[0], "unset"))
		my_unset(data, list->argv);
	else if (!ft_strcmp_built(list->argv[0], "export"))
		my_export(data, list->argv);
	else
	{
		g_err_no = 127;
		ft_printf("minishell: %s: command not found\n", list->argv[0]);
	}
	return (1);
}
