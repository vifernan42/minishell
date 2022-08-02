/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:09:27 by vifernan          #+#    #+#             */
/*   Updated: 2022/07/27 21:09:30 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
