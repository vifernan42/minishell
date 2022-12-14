/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2022/12/14 19:43:55 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	execution(t_pipe *list, t_data *data, int *pipe_fd)
{
	int pid;

	pid = fork();
	if (pid < 0)
	{
		close(pipe_fd[WR_END]);
		close(pipe_fd[RD_END]);
		perror("minishell: PID error\n");
	}
	else if (pid == 0)
	{
		if (list->in_fd)
		{
			dup2(list->in_fd, STDIN_FILENO);
			close(list->in_fd);
		}
		if (list->out_fd != 1)
		{
			dup2(list->out_fd, STDOUT_FILENO);
			close(list->out_fd);
		}
		else if(list->next && list->out_fd)
			dup2(pipe_fd[WR_END], STDOUT_FILENO);
		close(pipe_fd[WR_END]);
		close(pipe_fd[RD_END]);
		if (execve(list->exec_path, list->argv, data->env) == -1)
			perror("Execution error\n");
		exit (0);
	}
	else
	{
		if (list->in_fd > 2)
			close(list->in_fd);
		if (list->out_fd > 2)
			close(list->out_fd);
		close(pipe_fd[WR_END]);
		if (list->next && !list->next->in_fd)
			list->next->in_fd = pipe_fd[RD_END];
		else
			close(pipe_fd[RD_END]);
		if (list->in_fd > 2)
			close(list->in_fd);
		if (list->out_fd > 2)
			close(list->out_fd);
		data->wait++;
	}
}

void	exec_builtins(t_pipe *list, t_data *data)
{
	if (!ft_strcmp("pwd", list->argv[0]))
		pwdcurrent(list);
	else if (!ft_strcmp("echo", list->argv[0]))
		my_echo(data, list->argv, list->out_fd);
	else if (!ft_strcmp("exit", list->argv[0]))
		my_exit();
	else if (!ft_strcmp("env", list->argv[0]))
		env(data->env, list->out_fd);
	else if (!ft_strcmp("cd", list->argv[0]))
		my_chdir(data, list->argv[1]);
	else if (!ft_strcmp("unset", list->argv[0]))
		my_unset(data, list->argv);
	else if (!ft_strcmp("export", list->argv[0]))
		my_export(data, list->argv);
	else
		printf("NOT FOUND: 	%s\n", list->argv[0]);
}

void	exec_pipes(t_pipe *list, t_data *data)
{
	t_pipe	*next;
	int		pipe_fd[2];

	if (pipe(pipe_fd) < 0)
	{
		perror("minishell: PIPE error\n");
		return ;
	}
	if (!list->next && !list->out_fd)
	  	list->out_fd = STDOUT_FILENO;
	if (!list->exec_path)
		exec_builtins(list, data);
	else
		execution(list, data, pipe_fd);
	next = list->next;
	if (next)
		exec_pipes(next, data);
	while (data->wait-- > 0)
		waitpid(-1, NULL, 0);
}