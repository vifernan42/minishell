/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vifernan <vifernan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 18:42:14 by ialvarez          #+#    #+#             */
/*   Updated: 2022/12/13 20:17:24 by vifernan         ###   ########.fr       */
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
#include <sys/types.h>
#include <dirent.h>
#include <libgen.h>
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
	int		wait;
	int		err;
}		t_data;


/* -- parse -- */
int		pipe_parse(t_data *data);
int		even_quotes(char *s, int count, char x, t_data *data);
int		syntax_char(char *ch, int fd);
char	**cmd_arg_quottes(char	*pipe);

/* -- fill struct --*/
char	*get_promt(char *user);
char	**keep_env(char **env);

/* -- tokenizator -- */
t_pipe	*tokenizator(t_data *data, int i);
t_pipe	*create_node(char *cmd_stg, char *all_path, t_data *data);
int		take_heredoc(char **aux_cmd, int i, char **cmd_sp, char *aux);
void 	take_redirec(char **aux_cmd, int i, char **cmd_sp, t_pipe *ret);
void	take_args(char **cmd_sp, t_pipe *ret, char *all_path);
int		find_heredir(char **cmd_sp, int i, int type);
char	*find_key(char *str, int i, int j);
char	*ret_key(char *str, int i, int j, char c);
int		find_rm_size(char *str, int i, int lock, int type);

/* -- exec -- */
void	exec_pipes(t_pipe *list, t_data *data);

/* -- rm_used -- */
char	*rm_used(char **cmd_sp, int i, int f, int size);
char	*ret_value(char *ret);
char	*find_middle(char *str, int type);
char	*join_swap(char	*str, char	*str2, int flag);

/* -- built-ins -- */
int		pwdcurrent();
int		echos(char **argv, int fd);
void	my_exit();
int		env(char **envu, int fd);
int		my_chdir(t_data *data, const char *path);
void	my_unset(t_data *data, char *key);


/* -- leaks -- */
void	leaks(void);

#endif


