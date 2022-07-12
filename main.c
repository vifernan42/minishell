/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/12 13:49:44 by vifernan         ###   ########.fr       */
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

char	*skip_quotes(char *in_promp)
{
	int		i;
	//char	*out_promp;

	i = -1;
	while (in_promp[++i] != '\0')
	{
		if (in_promp[i] == 39 || in_promp[i] == '"')
		{
			while ((in_promp[i++] != 39 || in_promp[i] != '"') && in_promp[i] != '\0')
			{
				if (in_promp[i] == '"')
					break ;
				printf("%c", in_promp[i]);
			}
			if (in_promp[i] == '\0')
				return (0);
		}
	}
	return (0);
}


int main()
{

	t_data	data;
	char	*cmd_line;
	//char	*val;
	int		i;

	atexit(leaks);
	data.promt = get_promt(getenv("USER"), &data);
	while(1)
	{
		cmd_line = readline (data.promt);
		//val = skip_quotes(cmd_line);
		data.spt_pipes = st_split(cmd_line, '|');
		i = -1;
		while (data.spt_pipes[++i] != NULL)
			printf("%s\n", data.spt_pipes[i]);
		//printf("%s\n", val); 
		//save_right_cmd(cmd_line);
		free (cmd_line);
		//exit(0);
	}
}
