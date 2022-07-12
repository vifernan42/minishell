/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 17:36:59 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/12 20:08:43 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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


void	check_tofill(char **aux) // revisar y meter un a uno saltando las comillas
{
	int	i;

	i = -1;
	while (aux[++i] != NULL)
		printf("%s\n", aux[i]);
}

void	fill_it(t_data *data) // recorrer los pipes
{
	char	**aux;
	int		j;

	j = -1;
	while (data->spt_pipes[++j] != NULL)
	{
		aux = st_split(data->spt_pipes[j], ' ');
		check_tofill(aux);
		free(aux);
	}
}

void	even_quotes(char *s)
{
	int		i;
	int		count;
	char	x;

	i = -1;
	x = 0;
	count = 0;
	while(s[++i] != '\0')
	{
		if ((s[i] == '\"' || s[i] == '\'') && count++)
		{
			if (s[i] == '\'')
				x = '\'';
			else
				x = '\"';
			while (s[++i] != x && s[i] != '\0');
			if (s[i] == x)
				count++;
		}
		if (count % 2 != 0)
		{
			ft_putstr_fd("minishell: syntax error \" not found", STDERR_FILENO); //funcion de identificar caracter o palabra ex: "
			exit(0);
		}
	}
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
		even_quotes(cmd_line);
		data.spt_pipes = st_split(cmd_line, '|');
		fill_it(&data);
		free (cmd_line);
	}
}
