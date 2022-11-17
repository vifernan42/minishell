/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2022/11/17 13:16:44 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int		exec_built(t_data *data, t_pipe *list, )
void	execution(t_pipe *list, t_data *data, int *pipe_fd)
{
	int pid;

	pid = fork();
	//printf("pid--> %d\n %s\n", pid, *list->argv);
	if (pid < 0)
	{
		close(pipe_fd[WR_END]);
		close(pipe_fd[RD_END]);
		perror("minishell: PID error\n");
	}
	else if (pid == 0)
	{
		// printf("IN-> %d | %d\n", pid, list->in_fd);
		close(pipe_fd[RD_END]);
		if (list->in_fd)
		{
			dup2(list->in_fd, STDIN_FILENO);
			close(list->in_fd);
		}
		if (!list->next && list->out_fd != 1)
		{
			dup2(list->out_fd, STDOUT_FILENO);
			close(list->out_fd);
		}
		if(list->next)
			dup2(pipe_fd[WR_END], STDOUT_FILENO);
		close(pipe_fd[WR_END]);
	//	write(1, "entra\n", 6);
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
		{
			list->next->in_fd = pipe_fd[RD_END];
		}
		else
			close(pipe_fd[RD_END]);
		data->wait++;
	//	write(1, "ent\n", 4);
	}
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
	printf("path--> %s\n", list->exec_path);
	execution(list, data, pipe_fd);
	next = list->next;
	if (next)
		exec_pipes(next, data);
	while (data->wait-- > 0)
		waitpid(-1, NULL, 0);
}