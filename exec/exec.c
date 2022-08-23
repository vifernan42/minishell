/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:03:56 by vifernan          #+#    #+#             */
/*   Updated: 2022/08/23 16:45:52 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lets_pipe(t_pipe *pipe)
{
	int	pid;
	pid = fork();
}

void	exec_pipes(t_pipe *pipe)
{
	t_pipe	*next_p;

	if (pipe->next)
		lets_pipe(pipe);
}