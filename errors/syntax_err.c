/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 21:10:29 by vifernan          #+#    #+#             */
/*   Updated: 2022/12/14 19:12:41 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	syntax_char(char *ch, int fd)
{
	char	*s;

	s = ft_strdup("-minishell: syntax error near unexpected token ");
	if (s != NULL)
		write(fd, s, ft_strlen(s));
	write(fd, "`", 1);
	if (ch != NULL)
		write(fd, ch, ft_strlen(ch));
	write(fd, "\'\n", 2);
	free(s);
	free(ch);
	return (1);
}
