/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:42:14 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/05 18:30:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	"libft/libft.h"

typedef struct s_data {
	char	**env;
	char	*env_user;
	char	*promt;
}		t_data;

int	echos(char **argv, int fd);

#endif


