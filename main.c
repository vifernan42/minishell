/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/01 17:26:57 by ialvarez         ###   ########.fr       */
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

/* En el main damos tamaño en el st split*/
int	main(void) /* get_env */
{
	t_data	data;
	t_pipe	*pipe;
	char	*cmd_line;

	//atexit(leaks);
	while (1)
	{
		data.promt = get_promt(getenv("USER"));
		cmd_line = readline (data.promt);
		if (even_quotes(cmd_line, 0, 0) == 0)
		{
			data.spt_pipes = st_split(cmd_line, '|');
			if (pipe_parse(&data) == 0)
				pipe = tokenizator(&data, -1);
		}
		free(cmd_line);
		free(data.promt);
		leaks();
	}
}
