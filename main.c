/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/17 18:41:38 by vifernan         ###   ########.fr       */
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
	if (pipe->in_fd)
		close(pipe->in_fd);
	if (pipe->out_fd)
		close(pipe->out_fd);
	if (pipe->out_name)
		free(pipe->out_name);
	if (pipe->in_name)
		free(pipe->in_name);
	if (pipe->err)
		free(pipe->err);
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
	*next = pipe->next;
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

int	main(void) /* get_env */
{
	t_data	data;
	t_pipe	*pipe;
	char	*cmd_line;
	int		i;

	while (1)
	{
		data.all_path = get_promt(getenv("PATH"));
		data.promt = get_promt(getenv("USER"));
		cmd_line = readline (data.promt);
		i = 0;
		while (cmd_line[i] == ' ')
			i++;
		if (cmd_line[i] != '\0')
		{
			data.spt_pipes = st_split(cmd_line, '|');
			if (even_quotes(cmd_line, 0, 0, &data) == 0) /* revisar <<< o >>> */
			{	
				pipe = tokenizator(&data, -1);
				print_list(pipe);
				lstdelete(pipe);
			}
			free_matrix(data.spt_pipes);
		}
		add_history(cmd_line);
		free(cmd_line);
		free(data.promt);
		free(data.all_path);
		system("leaks minishell");
	}
}
