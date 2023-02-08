/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 20:06:04 by vifernan          #+#    #+#             */
/*   Updated: 2023/02/08 20:35:55 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//char	*var_tochange()
/*
char	*value_to_expand(char *var_env, char *var_name, int start, int end)
{
	char	*str;
	char	*aux;
	char	*enxpand;
	
	aux = ft_substr(var_env, 0, i - 1);
	str = ft_strjoin(aux, var_name);
	free(aux);
	if (char_index > 0)
	{
		aux = ft_substr(var_env, start, end);
		*enxpand = ft_strjoin(str, aux);
		free(aux);
	}
	else
		*enxpand = ft_strdup(str);
	free(str);
	free(var_env);
	return (0);
}*/

int	change_value(char *str, int i, t_data *data, char **expand_ln)
{
	char	*var_name;
	int		char_index;
	char	*var_env;
	char	*aux;
	int		leng;
	
	leng = 0;
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
	free(*expand_ln);
	*expand_ln = value_to_expand(var_env, var_name, i + char_index, leng - (i + char_index));
	aux = ft_substr(var_env, 0, i - 1);
	str = ft_strjoin(aux, var_name);
	free(aux);
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

int	check_before_change(char *str, int i, int *here, int *open)
{
	if (i > 0 && str[i] == '<' && str[i - 1] == '<')
		*here = 1;
	else if (str[i] != '\'' && str[i] != '\"' && str[i] != ' ' && str[i] != '$')
		*here = 0;
	if (str[i] == '\'')
	{
		if (*open)
			*open = 0;
		else
			*open = 1;
	}
	//printf("%d\n", *here);
	if (!*open && !*here)
		return (0);
	else
		return (1);
}

char	*take_variable(t_data *data, char *str)
{
	int	i;
	int	open;
	char *expand_ln;
	int	here;
	
	i = -1;
	open = 0;
	expand_ln = NULL;
	here = 0;
	while (str[++i] != '\0')
	{
		if (!check_before_change(str, i, &here, &open) && str[i] == '$')
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
			if (aux[i][0] == '\0')
				count++;
		if (i == count)
		{
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
	if (line[i] == '<' || line[i] == '>' || line[i] == ';'
		|| line[i] == '\\')
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
			if (aux_line(line, i - 1) == 1)
				return (1);
		}
		else if (line[i] == '>' && (line[i + 1] == ' ' || line[i + 1] == '\0'))
		{
			i++;
			while (line[i] == ' ' && line[i] != '\0')
				i++;
			if (aux_line(line, i - 1) == 1)
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
		return (syntax_char(ft_charjoin('|'), STDERR_FILENO));
	return (check_line(s, data));
}
