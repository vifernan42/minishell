/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2023/02/23 19:01:43 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_promt(char *user)
{
	if (!user)
		return (ft_strjoin("ghost", "@minishell: $ "));
	return (ft_strjoin(user, "@minishell: $ "));
}

static char	**keep_env(char **env)
{
	char	**envir;
	int		i;
	int		j;

	i = 0;
	while (env[i] != NULL)
		i++;
	envir = (char **)malloc((i + 1) * sizeof(char *));
	i = -1;
	while (env[++i] != NULL)
	{
		j = -1;
		envir[i] = (char *)malloc((int)ft_strlen(env[i]) + 1 * sizeof(char));
		while (env[i][++j] != '\0')
			envir[i][j] = env[i][j];
		envir[i][j] = '\0';
	}
	envir[i] = NULL;
	return (envir);
}

static char	*start_variables(int argc, char **argv, char **envp, t_data *data)
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

static void	ready_to_start(t_data *data, char *cmd_line)
{
	t_pipe	*pipe;

	data->spt_pipes = st_split(cmd_line, '|');
	if (data->spt_pipes[0] && even_quotes(cmd_line, 0, 0, data) == 0)
	{
		pipe = tokenizator(data, -1);
		if (data->err != -1 && pipe)
			exec_pipes(pipe, data);
		if (pipe)
			lstdelete(pipe);
	}
	if (data->spt_pipes)
		free_matrix(data->spt_pipes);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*cmd_line;
	int		i;

	cmd_line = start_variables(argc, argv, envp, &data);
	while (cmd_line)
	{
		i = 0;
		cmd_line = start_variables(0, argv, envp, &data);
		if (!cmd_line)
			ft_printf("exit\n");
		else
			while (cmd_line[i] == ' ')
				i++;
		if (cmd_line && cmd_line[i] != '\0' && (int)ft_strlen(cmd_line + i) > 0)
			ready_to_start(&data, cmd_line);
		free_variables(cmd_line, &data);
	}
}
