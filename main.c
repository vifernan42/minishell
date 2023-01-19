/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/19 19:17:10 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

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
	while(pipe)
	{
		nodedelete(pipe, &next);
		pipe = next;
	}
}

void	print_node(t_pipe *pipe, t_pipe **next)
{
	(void)next;
	if (pipe->exec_path)
		printf("exec_path:	%s\n", pipe->exec_path);
	if (pipe->argv)
		for(int i = 0; pipe->argv[i] != NULL; i++)
			printf("cmd_arg[%d]:	%s\n", i, pipe->argv[i]);
	if (pipe->in_fd)
		printf("in_fd:	%d\n", pipe->in_fd);
	if (pipe->out_fd)
		printf("out_fd:	%d\n", pipe->out_fd);
}

void	print_list(t_pipe *pipe)
{
	t_pipe	*next;
	int		num;
	
	if (!pipe)
		return ;
	next = NULL;
	num = 1;
	while(pipe)
	{
		printf("--NODE %d--\n", num++);
		print_node(pipe, &next);
		pipe = pipe->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	t_pipe	*pipe;
	char	*cmd_line;
	int		i;
	
	(void)argc;
	(void)argv;
	//ft_signal();
	/*signal(SIGINT, handle_signal);
	if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
    {
        printf("Error setting SIGQUIT handler\n");
        exit(1);
    }*/
	data.env = keep_env(envp);
//	print_matrix(data.env);
	while (1)
	{
		select_signal(0);
		err_no = 0;
		data.wait = 0;
		data.all_path = get_promt(getenv("PATH"));
		//printf("AQUI\n");
		data.promt = get_promt(getenv("USER"));
		cmd_line = readline(data.promt);
		i = 0;
		if (cmd_line == NULL)
		{
			printf("exit\n");
			//printf("%sexit\n", data.promt);
			break ;
		}
		while (cmd_line[i] == ' ')
			i++;
		if (cmd_line[i] != '\0')
		{
			data.spt_pipes = st_split(cmd_line, '|');
			if (even_quotes(cmd_line, 0, 0, &data) == 0)
			{	
				pipe = tokenizator(&data, -1);
				if (data.err != -1) /* la -ls (example) */
					exec_pipes(pipe, &data);
				lstdelete(pipe);
			}
			//if (data.err != 2)
				free_matrix(data.spt_pipes);
		}
		add_history(cmd_line);
		free(cmd_line);
		free(data.promt);
		free(data.all_path);
		//env_update(&data, ft_strjoin("?=", ft_itoa(err_no)), "?");
		system("leaks minishell");
		//return (0);
	}
}
