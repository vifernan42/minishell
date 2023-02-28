/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/28 21:39:22 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_process(t_pipe *list, t_data *data, int *pipe_fd)
{
	if (list->in_fd >= 2)
		close(list->in_fd);
	if (list->out_fd >= 2)
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

static void	child_process(t_pipe *list, t_data *data, int *pipe_fd)
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
	else if (list->next && list->out_fd)
		dup2(pipe_fd[WR_END], STDOUT_FILENO);
	if (!exec_killers_builtins(list, data, pipe_fd))
	{
		if (execve(list->exec_path, list->argv, data->env) == -1)
		{
			g_err_no = 126;
			ft_printf("minishell: %s: ", list->argv[0]);
			perror("");
		}
		exit (0);
	}
}

static void	execution(t_pipe *list, t_data *data, int *pipe_fd)
{
	int		pid;
	char	*level;

	pid = fork();
	level = NULL;
	if (!ft_strcmp_built(list->argv[0], "./minishell"))
	{
		data->level++;
		level = ft_itoa(data->level);
		update_env_var(data, ft_strjoin("SHLVL=", level), "SHLVL=");
		free(level);
	}
	if (pid < 0)
	{
		close(pipe_fd[WR_END]);
		close(pipe_fd[RD_END]);
		perror("minishell: PID error\n");
	}
	else if (pid == 0)
		child_process(list, data, pipe_fd);
	else
		parent_process(list, data, pipe_fd);
}

void	exec_pipes(t_pipe *list, t_data *data)
{
	t_pipe	*next;
	int		pipe_fd[2];
	int		bultins;

	bultins = 0;
	if (pipe(pipe_fd) < 0)
	{
		perror("minishell: PIPE error\n");
		return ;
	}
	if (!list->next && !list->out_fd)
		list->out_fd = STDOUT_FILENO;
	if (!exec_builtins(list, data) && list->argv)
		execution(list, data, pipe_fd);
	next = list->next;
	if (next)
		exec_pipes(next, data);
	while (data->wait-- > 0)
		waitpid(-1, &g_err_no, 0);
}
