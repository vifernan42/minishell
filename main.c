/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/05 20:09:33 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getenv( const char *name );

void leaks(void)
{
	system("leaks minishell");
}

char	*get_promt(char *user, t_data *data)
{
	if (user != NULL)
		data->env_user = strdup(user);
	else
		data->env_user = strdup("ghost");
	return (ft_strjoin(data->env_user, "@minishell: $ "));
}

void	do_something(char *cmd_line)
{
	if (ft_strncmp(cmd_line, "pwd", 4) == 0)
		printf("hola");
}

int main()
{

	t_data	data;
	char	*cmd_line;

	//atexit(leaks);
	data.promt = get_promt(getenv("USER"), &data);
	while(1)
	{
		cmd_line = readline (data.promt);
		do_something(cmd_line);
		free (cmd_line);
		//exit(0);
	}
}
