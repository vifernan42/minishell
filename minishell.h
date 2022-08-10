/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:42:14 by ialvarez          #+#    #+#             */
/*   Updated: 2022/08/10 17:08:56 by vifernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include	<unistd.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<readline/readline.h>
# include	<readline/history.h>
# include	<fcntl.h>
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
	char	*all_path;
	char	*env_user;
	char	*promt;
	char	**spt_pipes;
}		t_data;

int		pipe_parse(t_data *data);
int		even_quotes(char *s, int count, char x, t_data *data);
//int		echos(char **argv, int fd);
//char|\\\*pwdcurrent();
char	*get_promt(char *user);

/* errors */
int		syntax_char(char *ch, int fd);

char	**cmd_arg_quottes(char	*pipe);

/* tokenizator */
int	take_heredoc(char **aux_cmd, int i, char **cmd_sp, char *aux);
t_pipe	*create_node(char *cmd_stg, char *all_path);
t_pipe	*tokenizator(t_data *data, int i);
void 	take_redirec(char **aux_cmd, int i, char **cmd_sp, t_pipe *ret);
char	*ft_strjoin_swap(char	*str, char	*str2);
char	*rm_heredoc(char **cmd_sp, int i, int lock);
int	find_heredoc(char **cmd_sp, int i, int x);
void	take_args(char **cmd_sp, t_pipe *ret, char *all_path);
char	*find_key(char *str, int i, int j);
char	*ret_key(char *str, int i, int j, char c);

void	leaks(void);

#endif


