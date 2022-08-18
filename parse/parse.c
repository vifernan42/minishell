/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:06:04 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/18 17:41:25 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	more_redir(t_data *data, int i, int j, char **aux)
{	/* parsear <<"eo<f">hola <fila1 */
	int	found;

	found = 0;
	while (data->spt_pipes[++i] != NULL)
	{
		aux = cmd_arg_quottes(data->spt_pipes[i]);
		j = -1;
		while (aux[++j] != NULL)
		{
			found = find_rm_size(aux[j], 0, 0, -1);
			/* encontrar posibilidades de fallo */
			if (ft_strnstr(aux[j], "<<<", ft_strlen(aux[j]))
					|| ft_strnstr(aux[j], ">>>", ft_strlen(aux[j])))
			{
				if (ft_strnstr(aux[j], "<", ft_strlen(aux[j])))
					syntax_char(ft_charjoin('<'), STDERR_FILENO);
				else
					syntax_char(ft_charjoin('>'), STDERR_FILENO);
				free_matrix(aux);
				return (1);
			}
		}
		free_matrix(aux);
	}
	return (0);
}

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
			if (aux[i][0] == '\0')
				count++;
		}
		if (i == count)
		{
			syntax_char(ft_charjoin('|'), STDERR_FILENO);
			free_matrix(aux);
			free_matrix(data->spt_pipes);
			return (1);
		}
		free_matrix(aux);
	}
	return(more_redir(data, -1, -1, NULL));
}

int	even_quotes(char *s, int count, char x, t_data *data)
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
	return (pipe_parse(data));
}
