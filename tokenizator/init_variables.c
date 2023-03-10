/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_variables.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:51:35 by vifernan          #+#    #+#             */
/*   Updated: 2023/03/06 16:55:43 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_promt(char *user)
{
	if (!user)
		return (ft_strjoin("ghost", "@minishell: $ "));
	return (ft_strjoin(user, "@minishell: $ "));
}

char	**keep_env(char **env)
{
	char	**envir;
	int		i;
	int		j;

	i = 0;
	if (!env)
		return (NULL);
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

void	starting_var(int argc, char **argv, char **envp, t_data *data)
{
	char	*join;

	join = NULL;
	(void)argc;
	(void)argv;
	if (envp[0])
	{
		data->env = keep_env(envp);
		data->level = ft_atoi(search_variable(data->env, "SHLVL="));
		data->level++;
		join = ft_itoa(data->level);
		update_env_var(data, ft_strjoin("SHLVL=", join), "SHLVL=");
		free(join);
	}
	else
		data->env = NULL;
	if (data->env)
	{
		data->level = ft_atoi(search_variable(data->env, "SHLVL="));
		join = ft_itoa(g_err_no);
		env_update(data, ft_strjoin("?=", join), "?=");
		free(join);
	}	
}

char	*start_variables(int argc, char **argv, char **envp, t_data *data)
{
	if (argc != 0)
	{
		starting_var(argc, argv, envp, data);
		return ("");
	}
	else
	{
		select_signal(0);
		g_err_no = 0;
		data->wait = 0;
		if (data->env)
		{
			data->all_path = ft_strdup(search_variable(data->env, "PATH="));
			data->promt = get_promt(search_variable(data->env, "USER="));
		}
		else
		{
			data->all_path = NULL;
			data->promt = get_promt(NULL);
		}
		return (readline(data->promt));
	}	
}
