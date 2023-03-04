/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 18:51:00 by vifernan          #+#    #+#             */
/*   Updated: 2023/03/02 18:47:54 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_killers_builtins(t_pipe *list, t_data *data, int *pipe_fd)
{
	if (list->exec_path)
	{
		close(pipe_fd[WR_END]);
		close(pipe_fd[RD_END]);
		return (0);
	}
	if (!ft_strcmp_built(list->argv[0], "pwd"))
		pwdcurrent(list, data);
	else if (!ft_strcmp_built(list->argv[0], "env")
		|| !ft_strcmp_built(list->argv[0], "ENV"))
		env(data->env, list->out_fd);
	else
	{
		g_err_no = 127;
		ft_printf("minishell: %s: command not found\n", list->argv[0]);
	}
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
		|| !ft_strcmp_built(list->argv[0], "ENV"))
		return (0);
	if (!ft_strcmp_built(list->argv[0], "echo"))
		my_echo(list->argv, list->out_fd);
	else if (!ft_strcmp_built(list->argv[0], "exit"))
		my_exit(data);
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
