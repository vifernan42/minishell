/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <ialvarez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 20:10:06 by ialvarez          #+#    #+#             */
/*   Updated: 2023/01/19 19:24:28 by ialvarez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_variable(char **env, char *str, int i, int fd)
{
	char	*var_name;
	int		char_index;
	char	*var_env;
	
	char_index = ft_charindex(str + i, ' ') - 1;
	/*if (ft_charindex(str + i, '\'') - 1 < char_index)
		char_index = ft_charindex(str + i, '\'') - 1;*/
	if (char_index > 0)
		var_name = ft_substr(str + i, 1, char_index);
	else
	{
		char_index = ft_charindex(str + i, '\"');
		if (char_index < 0)
		{
			char_index = ft_charindex(str + i + 1, '$');
			if (char_index < 0)
				char_index = (int)ft_strlen(str + i);
			var_name = ft_substr(str + i, 1, char_index);
			
		}
		else
			var_name = ft_substr(str + i, 1, char_index - 1);
	}
	var_env = var_name;
	free(var_name);
	var_name = ft_strjoin(var_env, "=");
	var_env = search_variable(env, var_name);
	if (var_env)
		ft_putstr_fd(var_env, fd);
	free(var_name);
	return (char_index);
}

void	do_echo(char **env, char *str, int fd)
{
	int		i;
	char	c;
	int		open;

	i = -1;
	c = 0;
	open = 0;
	(void)env;
	while (str[++i] != '\0')
	{
		/*if (str[i] == '\'' || str[i] == '\"')
		{
			if (open == 1)
			{
				if (c != str[i])
					write(fd, &str[i], 1);
				c = 0;
				open = 0;
			}
			else
				open = 1;
			c = str[i];
		}
		else if (str[i] == '$' && ((c == '\"' && open == 1) || (c == 0 && open == 0)))
			i += print_variable(env, str, i, fd);
		else*/
			write(fd, &str[i], 1);
	}
}

int my_echo(t_data *data, char **argv, int fd)
{
	int flag;
	int i;

	flag = 0;
	i = 1;
	if (ft_strcmp(argv[1], "-n"))
		flag = 1;
	i = 1;
	if (flag != 1)
		i++;
	while (argv[i] != NULL)
	{
		do_echo(data->env, argv[i], fd);
		if (argv[i + 1] != NULL)
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (flag == 1)
		ft_putstr_fd("\n", fd);
	return (1);
}