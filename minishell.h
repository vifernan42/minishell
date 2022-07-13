/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialvarez <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:42:14 by ialvarez          #+#    #+#             */
/*   Updated: 2022/07/13 20:08:58 by vifernan         ###   ########.fr       */
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

typedef struct s_pipe
{
	char			*exec_path; //path ejecucion
	char			**argv; //ls -la lewn lwleel
	int				in_fd; //fd entrada
	int				out_fd; //fd de salidaa
	char			**out_name; //fichero de salida?
	char			**in_name; //fichero de entrada?
	struct s_pipe	*next;
}				t_pipe;

typedef struct s_data {
	char	**env;
	char	*env_user;
	char	*promt;
	char	**spt_pipes;
}		t_data;

int		pipe_parse(t_data *data);
int		even_quotes(char *s, int count, char x);
//int		echos(char **argv, int fd);
//char|\\\*pwdcurrent();
char	*get_promt(char *user, t_data *data);
int		syntax_char(char *ch, int fd);

#endif


