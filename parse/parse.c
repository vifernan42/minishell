/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:06:04 by vifernan          #+#    #+#             */
/*   Updated: 2023/01/30 19:58:15 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_value(char *str, int i, t_data *data, char **expand_ln)
{
	char	*var_name;
	int		char_index;
	char	*var_env;
	char	*aux;
	int		leng;
	
	leng = 0;
	data->err = 0;
	aux = NULL;
	char_index = ft_strinkey(str + i, "$,. ><-@?¿¡/\\%#·\"\'");
	leng = (int)ft_strlen(str);
	if (char_index == 0 && str[i] == '?')
		char_index = 1;
	var_name = ft_substr(str + i, 0, char_index);
	var_env = ft_strjoin(var_name, "=");
	free(var_name);
	var_name = search_variable(data->env, var_env);
	
	if (!var_name)
		var_name = "";
	free(var_env);
	var_env = ft_strdup(str);
	free(str);
	aux = ft_substr(var_env, 0, i - 1);
	str = ft_strjoin(aux, var_name);
	free(aux);
	free(*expand_ln);
	if (char_index > 0)
	{
		aux = ft_substr(var_env, (i + char_index), leng - (i + char_index));
		*expand_ln = ft_strjoin(str, aux);
		free(aux);
	}
	else
		*expand_ln = ft_strdup(str);
	free(str);
	free(var_env);
	
	return (0);
}

char	*take_variable(t_data *data, char *str)
{
	int	i;
	int	open;
	char *expand_ln;
	
	i = -1;
	data->err = 0;
	open = 0;
	expand_ln = NULL;
	while (str[++i] != '\0')
	{
		if (str[i] == '\'')
		{
			if (open)
				open = 0;
			else
				open = 1;
		}
		if (str[i] == '$' && !open)
		{
			i = change_value(ft_strdup(str), i + 1, data, &expand_ln);
			if (expand_ln)
			{
				free(str);
				str = ft_strdup(expand_ln);
			}
		}
	}
	if (expand_ln)
		free(expand_ln);
	return (str);
}

int	more_redir(t_data *data, int i, int j, char **aux)
{
	int		found;
	char	*expand_ln;

	found = 0;
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
			found = find_rm_size(aux[j], 0, -1);
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
			data->err = 2;
			syntax_char(ft_charjoin('|'), STDERR_FILENO);
			free_matrix(aux);
			free_matrix(data->spt_pipes);
			return (1);
		}
		free_matrix(aux);
	}
	return (more_redir(data, -1, -1, NULL));
}

static int	aux_line(char *line, int i)
{
	if (line[i] == '<')
		syntax_char(ft_charjoin('<'), STDERR_FILENO);
	if (line[i] == '>')
		syntax_char(ft_charjoin('>'), STDERR_FILENO);
	if (line[i] == ';')
		syntax_char(ft_charjoin(';'), STDERR_FILENO);
	if (line[i] == '\\')
		syntax_char(ft_charjoin('\\'), STDERR_FILENO);
	if (line[i] == '\0')
		syntax_char(ft_charjoin('\0'), STDERR_FILENO);
	if (line[i] == '<' || line[i] == '>' || line[i] == ';'
		|| line[i] == '\\' || line[i] == '\0')
		return (1);
	return (0);
}

static int	check_line(char *line, t_data *data)
{
	int	i;

	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '<' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (aux_line(line, i) == 1)
				return (1);
		}
		else if (line[i] == '>' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		{
			i++;
			while (line[i] == ' ' && line)
				i++;
			if (aux_line(line, i) == 1)
				return (1);
		}
	}
	return (pipe_parse(data));
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
	{
		data->err = 2;
		return (syntax_char(ft_charjoin('|'), STDERR_FILENO));
	}
	return (check_line(s, data));
}
