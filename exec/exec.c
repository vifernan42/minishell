/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/23 18:32:22 by ialvarez         ###   ########.fr       */
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
	close(pipe_fd[WR_END]);
	close(pipe_fd[RD_END]);
	if (execve(list->exec_path, list->argv, data->env) == -1)
	{
		g_err_no = 126;
		ft_printf("minishell: %s: ", list->argv[0]);
		perror("");
	}
	exit (0);
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

static void	exec_builtins(t_pipe *list, t_data *data)
{
	if (!list->argv)
		return ;
	if (!ft_strcmp_built(list->argv[0], "pwd"))
		pwdcurrent(list, data);
	else if (!ft_strcmp_built(list->argv[0], "echo"))
		my_echo(list->argv, list->out_fd);
	else if (!ft_strcmp_built(list->argv[0], "exit"))
		my_exit(data);
	else if (!ft_strcmp_built(list->argv[0], "env"))
		env(data->env, list->out_fd);
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
		waitpid(-1, &g_err_no, 0);
}
