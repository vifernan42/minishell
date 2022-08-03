/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:42:14 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/02 18:16:54 by vifernan         ###   ########.fr       */
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
# include	"printf/ft_printf.h"

# define RD_END	0
# define WR_END	1

typedef struct s_pipe
{
	char			*exec_path; //path ejecucion
	char			**argv; //ls -la lewn lwleel
	int				in_fd; //fd entrada
	int				out_fd; //fd de salidaa
	char			*out_name; //fichero de salida?
	char			*in_name; //fichero de entrada?
	char			*err;
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
char	*get_promt(char *user);

/* errors */
int		syntax_char(char *ch, int fd);

char	**cmd_arg_quottes(char	*pipe);

/* tokenizator */
int	find_heredoc(char **cmd_sp, int i);
int	take_heredoc(char **aux_cmd, int i, char **cmd_sp, char *aux);
t_pipe	*create_node(char *cmd_stg);
t_pipe	*tokenizator(t_data *data, int i);

void	leaks(void);

#endif


