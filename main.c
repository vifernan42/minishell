/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/04 17:46:53 by vifernan         ###   ########.fr       */
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
/*
static void	ft_lstdelete(t_data *data, char(*del)(void *))
{
	if (!data)
		return ;
	del(data->env_user);
	del(data->env);
	del(data->promt);
	del(data->spt_pipes);
	free(data);
	data = NULL;
}*/

/* En el main damos tamaño a PIPE con tokenizator,
 * tambien a cmd_line le damos tamañ con el readline
 * aunque lo liberamos al final del main*/

void	print_pipe(t_pipe *pipe)
{
	int i = -1;
	
	printf("\nin_fd: %d\n", pipe->in_fd);
	printf("PATH: %s\n", pipe->exec_path);
	if (pipe->argv)
	{
		while (pipe->argv[++i] != NULL)
			printf("args[%d]:%s$\n", i, pipe->argv[i]);
	}
	printf("out_fd: %d\n\n", pipe->out_fd);
	
}

int	main(void) /* get_env */
{
	t_data	data;
	t_pipe	*pipe;
	char	*cmd_line;

	while (1)
	{
		data.all_path = get_promt(getenv("PATH"));
		data.promt = get_promt(getenv("USER"));
		cmd_line = readline (data.promt);
		if (even_quotes(cmd_line, 0, 0) == 0)
		{
			data.spt_pipes = st_split(cmd_line, '|');
			if (pipe_parse(&data) == 0) /* revisar <<< o >>> */
			{
				pipe = tokenizator(&data, -1);
				print_pipe(pipe);
			}
		}
		free(cmd_line);
		free(data.promt);
		free(data.all_path);
		//free(pipe);
		//system("leaks minishell");
	}
}
