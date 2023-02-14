/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 17:50:45 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/14 17:52:20 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_err_redir(char **aux, int j)
{
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
	if (ft_strnstr(aux[j], "<>", ft_strlen(aux[j]))
		|| ft_strnstr(aux[j], "><", ft_strlen(aux[j])))
	{
		if (ft_strnstr(aux[j], "<", ft_strlen(aux[j])))
			syntax_char(ft_charjoin('>'), STDERR_FILENO);
		else
			syntax_char(ft_charjoin('<'), STDERR_FILENO);
		free_matrix(aux);
		return (1);
	}
	return (0);
}

int	more_redir(t_data *data, int i, int j, char **aux)
{
	char	*expand_ln;

	expand_ln = NULL;
	while (data->spt_pipes[++i] != NULL)
	{
		expand_ln = take_variable(data, ft_strdup(data->spt_pipes[i]));
		if (expand_ln)
		{
			if (data->spt_pipes[i])
				free(data->spt_pipes[i]);
			data->spt_pipes[i] = ft_strdup(expand_ln);
			free(expand_ln);
		}
		aux = cmd_arg_quottes(data->spt_pipes[i], data);
		j = -1;
		while (aux[++j] != NULL)
		{
			if (check_err_redir(aux, j))
				return (1);
		}
		free_matrix(aux);
	}
	return (0);
}
