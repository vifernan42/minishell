/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:06:04 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/05 19:07:08 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*int	more_redir(t_data *data, int i)
{
	char	**aux;
	int		j;
	
	while (data->spt_pipes[++i] != NULL)
	{
		aux = cmd_arg_quottes(data->spt_pipes[i]);
		j = -1;
		while (aux[++j] != NULL)
		{
			if () condicion para return (1) si lo encientra "<<<" || "<< <hola"
			printf("+	%s\n", aux[j]);
		}
		free_matrix(aux);
	}
	return (0);
}*/

int	pipe_parse(t_data *data)
{
	char	**aux;
	int		j;
	int		i;
	int		count;

	j = -1;
	while (data->spt_pipes[++j] != NULL)
	{
		aux = st_split(data->spt_pipes[j], ' ');
		i = -1;
		count = 0;
		while (aux[++i] != NULL)
		{
			printf("-	%s\n", aux[i]);
			if (aux[i][0] == '\0')
				count++;
		}
		if (i == count)
		{
			syntax_char(ft_charjoin('|'), STDERR_FILENO);
			free_matrix(aux);
			return (1);
		}
		free_matrix(aux);
	}
	//return(more_redir(data, -1))
	return (0);
}

int	even_quotes(char *s, int count, char x)
{
	int		i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			count++;
			if (s[i] == '\'')
				x = '\'';
			else
				x = '\"';
			i++;
			while (s[i] != x && s[i] != '\0')
				i++;
			if (s[i] == x)
				count++;
		}
		if (count % 2 != 0)
			return (syntax_char(ft_charjoin(x), STDERR_FILENO));
	}
	if (--i && s[i] == '|')
		return (syntax_char(ft_charjoin('|'), STDERR_FILENO));
	return (0);
}
