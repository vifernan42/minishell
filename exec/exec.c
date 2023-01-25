/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/25 20:25:41 by ialvarez         ###   ########.fr       */
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
		{
			err_no = 126;  /*mirar*/
			ft_printf("minishell: %s: ", list->argv[0]);
			perror("");
		}
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

void	change_two_dots(char **str, char *path)
{
	int	i;
	int	index;
	char	*aux;

	i = -1;
	if (path && (int)ft_strlen(path) > 0)
	{
		while (path[++i] != '\0')
		{
			if (path[i] == '/')
				index = i;
		}
		aux = (char *)malloc(sizeof(char) * index + 1);
		i = -1;
		while (path[++i] != '\0')
		{
			if (i < index)
				aux[i] = path[i];
		}
		aux[index] = '\0';
		free(*str);
		*str = ft_strdup(aux);
		free(aux);
	}
	/*else*/
		
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
		if (!ft_strcmp_built(list->argv[1], ".."))
			change_two_dots(&list->argv[1], search_variable(data->env, "PWD="));
		if (access(list->argv[1], F_OK) == -1)
		{
			ft_printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
			update_env_var(data, ft_strdup(list->argv[1]), "PWD=");
			printf("list_argv1:%s$\n", list->argv[1]);
		}
		//printf("**	%s\n", list->argv[1]);
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
		err_no = 127;
		printf("minishell: %s: command not found\n", list->argv[0]);
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
		waitpid(-1, &err_no, 0);
}