/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/27 17:22:43 by vifernan         ###   ########.fr       */
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
	free(s);
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

char	**cmd_arg_quottes(char	*pipe)
{
	char	**aux_cmd;
	char	*aux;
	int		x;

	aux_cmd = spqu_split(skip_spaces(pipe), ' ');
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
	return (aux_cmd);
}

/* --tokenizator START-- */

int	find_heredoc(char **cmd_sp, int i)
{
	while (cmd_sp[++i] != NULL)
	{
		if (ft_strnstr(cmd_sp[i], "<<<", 3))
			printf("Error");
		if (ft_strnstr(cmd_sp[i], "<<", 2))
			break ;
	}
	if (cmd_sp[i] == NULL)
		return (-1);
	return (i);
}

/*
char	**delete_used_cmd(char **cmd_sp, int join, int i)
{
	char	**aux;
	int		x;
	int		j;

	if (i == -1)
		return (NULL);
	x = -1;
	while (cmd_sp[++x] != NULL);
	if (join > 0)
		aux = malloc(sizeof(char **) * x +1);
	else
		aux = malloc(sizeof(char**) * x);
	x = -1;
	j = 0;
	while (cmd_sp[++x] != NULL)
	{
		if ((join == 0 && x != i && x - 1 != i) || (join == 1 && x != i))
			aux[j++] = ft_strdup(cmd_sp[x]);
	}
	aux[j] = NULL;
	return (aux);
}
*/

int	take_heredoc(char *cmd_stg, int i)
{
	char	*key;
	int		join;
	int		fd;
	char	**cmd_sp;

	join = 0;
	fd = 0;
	cmd_sp = cmd_arg_quottes(cmd_stg);
	i = find_heredoc(cmd_sp, -1);
	if (i == -1)
	{
		free_matrix(cmd_sp);
		return (0);
	}
	if ((int)ft_strlen(cmd_sp[i]) > 2)
	{
		key = ft_substr(cmd_sp[i], 2, (int)ft_strlen(cmd_sp[i]) - 2);
		join++;
	}
	else
		key = ft_strdup(cmd_sp[i + 1]);
	printf("key->%s\n", key);
	//fd = do_heredoc(key);
	/*if (find_heredoc(cmd_sp, -1) == -1)
		return (fd);
	return (take_heredoc(cmd_sp, -1));*/
	free(key);
	free_matrix(cmd_sp);
	return (0);
}

t_pipe	*create_node(char *cmd_stg)
{
	t_pipe	*ret;

	if (!cmd_stg)
		return (NULL);
	ret = malloc(sizeof(t_pipe));
	ft_bzero(ret, sizeof(t_pipe));
	ret->in_fd = take_heredoc(cmd_stg, -1);
	//take_redirections(ret, cmd_sp);
	//take_args_path(ret_cmd_sp);
	return (ret);
}

t_pipe	*tokenizator(t_data *data, int i)
{
	t_pipe	*ret;
	t_pipe	*new;

	if (!data->spt_pipes)
		return (NULL);
	while (data->spt_pipes[++i] != NULL)
	{
		if (i == 0)
		{
			ret = create_node(data->spt_pipes[i]);
			new = ret;
		}
		else
		{
			new->next = create_node(data->spt_pipes[i]);
			new = new->next;
		}
		free(data->spt_pipes[i]);
	}
	free(data->spt_pipes);
	return (ret);
}

/* --tokenizator END-- */

int	main(void) /* get_env */
{
	t_data	data;
	t_pipe	*pipe;
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
				pipe = tokenizator(&data, -1);
		}
		free(cmd_line);
		free(data.promt);
		leaks();
	}
}
