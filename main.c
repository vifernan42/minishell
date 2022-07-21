/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/21 19:01:29 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	leaks(void)
{
	system("leaks minishell");
}

int	syntax_char(char *ch, int fd)
{
	char	*s;

	s = ft_strdup("-minishell: syntax error near unexpected token ");
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	write(fd, "`", 1);
	if (ch != NULL)
		write(fd, ch, ft_strlen(ch));
	write(fd, "\'\n", 2);
	return (1);
}

char	*get_promt(char *user, t_data *data)
{
	if (user != NULL)
		data->env_user = strdup(user);
	else
		data->env_user = strdup("ghost");
	return (ft_strjoin(data->env_user, "@minishell: $ "));
}

void	fill_list(char **aux_cmd)
{
	int i;

	i = -1;
	while (aux_cmd[++i] != NULL)
		printf("%s$\n", aux_cmd[i]);
}

void	cmd_arg_quottes(t_data *data, int i)
{
	char	**aux_cmd;
	char	*aux;
	int		x;

	while (data->spt_pipes[++i] != NULL)
	{
		aux_cmd = spqu_split(skip_spaces(data->spt_pipes[i]), ' ');
		x = -1;
		while (aux_cmd[++x] != NULL)
		{
			if (aux_cmd[x][0] != '$')
				aux = skip_quotes(skip_spaces(aux_cmd[x]));
			else
				aux = skip_spaces(aux_cmd[x]);
			free(aux_cmd[x]);
			aux_cmd[x] = ft_strdup(aux);
			free(aux);
		}
		fill_list(aux_cmd);
		free(aux_cmd);
	}
}

int	main(void) /* get_env */
{
	t_data	data;
	char	*cmd_line;

	//atexit(leaks);
	while (1)
	{
		data.promt = get_promt(getenv("USER"), &data);
		cmd_line = readline (data.promt);
		if (even_quotes(cmd_line, 0, 0) == 0)
		{
			data.spt_pipes = st_split(cmd_line, '|');
			if (pipe_parse(&data) == 0)
				cmd_arg_quottes(&data, -1);
		}
		free (cmd_line);
	}
}
