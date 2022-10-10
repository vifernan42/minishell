		/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/23 16:45:52 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*int		pipe_ret(t_pipe *list, t_data *data, int in_check)
{

}*/


void	exec_pipes(t_pipe *list, t_data *data)
{
	t_pipe	*next;
	int		pipe_fd[2];
	int		pid;
	int		status;

	ft_printf("PATH:	%s\n", list->exec_path);
	if (list->next)
	{
		if (list->next->in_fd)
			close(list->next->in_fd);
		if (pipe(pipe_fd) < 0)
		{
			ft_printf("Error PIPE\n");
			return ;
		}
		pid = fork();
		if (pid == 0)
		{
			if (!list->in_fd)
				list->in_fd = pipe_fd[RD_END];
			list->next->in_fd = pipe_fd[RD_END];
			close(pipe_fd[RD_END]);
			dup2(list->in_fd, STDIN_FILENO);
			if (!list->out_fd)
				list->out_fd = pipe_fd[WR_END];
			close(pipe_fd[WR_END]);
			dup2(list->out_fd, STDOUT_FILENO);
			data->wait++;
			ft_printf("1-data->wait:	%d\n", data->wait);
			execve(list->exec_path, list->argv, data->env);
		//	exit (0);
		}
		else
		{
			next = list->next;
			if(list->next)
				exec_pipes(next, data);
		}
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			if (!list->in_fd)
				dup2(list->in_fd, STDIN_FILENO);
			if (!list->out_fd)
				dup2(list->out_fd, STDIN_FILENO);
			data->wait++;
			ft_printf("2-data->wait:	%d\n", data->wait);
			execve(list->exec_path, list->argv, data->env);
		//	exit (0);
		}
	}
	ft_printf("data->wait:	%d\n", data->wait);
	while (data->wait-- >= 0)
		waitpid(-1, &status, 0);
}