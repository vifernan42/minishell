/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/11 16:19:33 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *getenv( const char *name );

char	*pwdcurrent()
{
	char	buff[FILENAME_MAX];
	char	*current;

	getcwd(buff, FILENAME_MAX);
	current = ft_strdup(buff);
	return (current);
}

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

void	save_right_cmd(char *cmd_line)
{
	if (ft_strncmp(cmd_line, "pwd", 4) == 0)
		printf("%s\n", pwdcurrent());
}

int		skip_quotes(char *in_pipe)
{
	int		i;
	int		q_1;
	int		q_2;

	i = -1;
	q_1 = 0;
	q_2 = 0;
	while (in_pipe[++i] != '\0')
	{
		if (in_pipe[i] == '"')
			q_1++;
		if (in_pipe[i] == 39)
			q_2++;
	}
	if (q_1 % 2 != 0 || q_2 % 2 != 0)
		return (-1);
	return (i);
}


int main()
{

	t_data	data;
	char	*cmd_line;
	int		val;

	atexit(leaks);
	data.promt = get_promt(getenv("USER"), &data);
	while(1)
	{
		cmd_line = readline (data.promt);
		val = skip_quotes(cmd_line);
		data.spt_pipes = ft_split(cmd_line, '|');
		printf("%d\n", val); 
		//save_right_cmd(cmd_line);
		free (cmd_line);
		//exit(0);
	}
}
