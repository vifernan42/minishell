/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2022/11/30 17:51:10 by vifernan         ###   ########.fr       */
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
		// printf("IN-> %d | %d\n", pid, list->in_fd);
		// printf("OUT-> %d | %d\n", pid, list->out_fd);
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
		data->wait++;
	}
}

void	exec_builtins(t_pipe *list)
{
	if (!ft_strcmp("pwd", list->argv[0]))
		pwdcurrent(list);
	else if (!ft_strcmp("echo", list->argv[0]))
		echos(list->argv, list->out_fd);
	else if (!ft_strcmp("env", list->argv[0]))
		printf("YES: 	%s\n", list->argv[0]);
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
		exec_builtins(list);
	else
		execution(list, data, pipe_fd);
	next = list->next;
	if (next)
		exec_pipes(next, data);
	while (data->wait-- > 0)
		waitpid(-1, NULL, 0);
}