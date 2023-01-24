/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/24 20:36:29 by ialvarez         ###   ########.fr       */
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
		data->wait++;
	}
}

void	 exec_builtins(t_pipe *list, t_data *data)
{
	if (!list->argv)
		return ;
	if (!ft_strcmp_built(list->argv[0], "pwd"))
		pwdcurrent(list, data);
	else if (!ft_strcmp_built(list->argv[0], "echo"))
		my_echo(list->argv, list->out_fd);
	else if (!ft_strcmp_built(list->argv[0], "exit"))
		my_exit();
	else if (!ft_strcmp_built(list->argv[0], "env"))
		env(data->env, list->out_fd);
	else if (!ft_strcmp_built(list->argv[0], "cd"))
	{
		//if (list->argv[1] == "..")
		//ex: list->argv[1] = /Users/ialvarez/Documents/minishell -> /Users/ialvarez/Documents
		//check: /Users/ialvarez/Documents
		//Example cd ..
		//print: cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory
		my_chdir(data, list->argv[1]);
	}
	else if (!ft_strcmp_built(list->argv[0], "unset"))
		my_unset(data, list->argv);
	else if (!ft_strcmp_built(list->argv[0], "export"))
		my_export(data, list->argv);
	else
	{
		data->status = 2;	/* echo $? aqui seria error 2*/
		printf("NOT FOUND: 	%s\n", list->argv[0]);
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
	if (!list->exec_path)			/*SHLVL=1; aqui hay que mirar lo de la ejecucion de la minishell*/
		exec_builtins(list, data);
	else
		execution(list, data, pipe_fd);
	next = list->next;
	if (next)
		exec_pipes(next, data);
	while (data->wait-- > 0)
		waitpid(-1, NULL, 0);
}