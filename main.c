/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/13 19:37:28 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "minishell.h"

char	*get_promt(char *user)
{
	if (!user)
		return (ft_strjoin("ghost", "@minishell: $ "));
	return (ft_strjoin(user, "@minishell: $ "));
}

void	nodedelete(t_pipe *pipe, t_pipe **next)
{
	if (pipe->exec_path)
		free(pipe->exec_path);
	if (pipe->argv)
		free_matrix(pipe->argv);
	*next = pipe->next;
	free(pipe);
}

void	lstdelete(t_pipe *pipe)
{
	t_pipe	*next;

	if (!pipe)
		return ;
	next = NULL;
	while (pipe)
	{
		nodedelete(pipe, &next);
		pipe = next;
	}
}
/*void	print_node(t_pipe *pipe, t_pipe **next)
{
	(void)next;
	if (pipe->exec_path)
		printf("exec_path:	%s\n", pipe->exec_path);
	if (pipe->argv)
	{
		for(int i = 0; pipe->argv[i] != NULL; i++)
			printf("cmd_arg[%d]:	%s\n", i, pipe->argv[i]);
	}
	if (pipe->in_fd)
		printf("in_fd:	%d\n", pipe->in_fd);
	if (pipe->out_fd)
		printf("out_fd:	%d\n", pipe->out_fd);
}*/

/*void	print_list(t_pipe *pipe)
{
	t_pipe	*next;
	int		num;

	if (!pipe)
		return ;
	next = NULL;
	num = 1;
	while (pipe)
	{
		printf("--NODE %d--\n", num++);
		print_node(pipe, &next);
		pipe = pipe->next;
	}
}*/

char	*start_variables(int argc, char **argv, char **envp, t_data *data)
{
	char	*join;

	join = NULL;
	if (argc != 0)
	{
		(void)argc;
		(void)argv;
		data->env = keep_env(envp);
		data->level = ft_atoi(search_variable(data->env, "SHLVL="));
		join = ft_itoa(g_err_no);
		env_update(data, ft_strjoin("?=", join), "?=");
		free(join);
		return ("");
	}
	else
	{
		select_signal(0);
		g_err_no = 0;
		data->wait = 0;
		data->all_path = get_promt(getenv("PATH"));
		data->promt = get_promt(getenv("USER"));
		return (readline(data->promt));
	}	
}

void	free_variables(char	*cmd_line, t_data *data)
{
	char	*join;

	add_history(cmd_line);
	free(cmd_line);
	free(data->promt);
	free(data->all_path);
	if (g_err_no == 256)
		g_err_no = 1;
	join = ft_itoa(g_err_no);
	env_update(data, ft_strjoin("?=", join), "?=");
	free(join);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_pipe	*pipe;
	char	*cmd_line;

	cmd_line = start_variables(argc, argv, envp, &data);
	while (cmd_line)
	{
		cmd_line = start_variables(0, argv, envp, &data);
		if (!cmd_line)
			ft_printf("exit\n");
		if (cmd_line && cmd_line[0] != '\0')
		{
			data.spt_pipes = st_split(cmd_line, '|');
			if (even_quotes(cmd_line, 0, 0, &data) == 0)
			{	
				pipe = tokenizator(&data, -1);
				if (data.err != -1)
					exec_pipes(pipe, &data);
				lstdelete(pipe);
			}
			free_matrix(data.spt_pipes);
		}
		free_variables(cmd_line, &data);
		system("leaks -q minishell");
	}
}
