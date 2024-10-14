#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <fcntl.h>
# include "../libft/libft.h"

extern int	g_exit;

typedef enum e_typefile
{
	INFILE = 1,
	OUTFILE = 2,
	HEREDOC = 3,
	APPEND = 4,
}	t_typefile;

typedef struct s_tabfile
{
	t_typefile			type;
	char				*filename;
	int					fd;
}	t_tabfile;

typedef struct s_tabcmd
{
	char				*cmd;
	struct s_tabfile	*file;
	int					nb_file;
	int					nb_cmd;
}	t_tabcmd;

typedef struct s_pipe
{
	int	read;
	int	write;
	int	pfd[2];
	int	cmd;
	int	pid;
	int	boolean;
}			t_pipe;

typedef struct s_envir
{
	char			**envi;
}			t_envir;

typedef struct s_init_files
{
	int		i;
	int		j;
	int		k;
	char	*str;
	char	*input_str;
}			t_init_files;

//parsing
void		parse(char *str, t_envir *envs);
int			check_redir(char *str);
int			check_number_redir(char *str);
int			check_quote(char *str);
int			check_pipe(char *str);
int			check_if_valid(char *str, int i);

//lexer
void		lexer(char *str, t_envir *envs);
int			lexer_2(char **seq, t_tabcmd *tabcmd, char *str, int i);

//init
int			number_file(char *str, int cmd);
int			number_cmd(char *str);

//utils
t_tabcmd	*init_tab(char *str);
t_envir		*get_env(char **env);

//files
int			files(char	*str, t_tabcmd *tabcmd, int k, char *input_str);
char		*recover_name(char *str, int i);
int			stock_files(char *str, int i, t_typefile tfile, t_tabfile *tabfile);
int			check(char *str, int i, char chevron, int event);

//here_doc
int			here_doc(char *str, t_tabcmd *tabcmd);
int			check_if_here_doc(char *str);
char		*recover_limiter(char *str, int i);
int			ft_heredoc_2(char *str, t_tabcmd *tabcmd);
int			open_heredoc(char *str, int i, t_tabfile *tabfile, int nb_file);
int			ft_read_heredoc(char *limiter, int file);

//utils
int			chevron(char *str);
int			isbetweenquote(char *str, int i);
int			is_white_space(char c);
char		*ft_expand(char *str, t_envir *envs);
char		*ft_recover_variable(char *name, t_envir *envs);
char		*ft_recover_name(char *str, int i);
int			ft_strncmp_without_ws(const char *s1, const char *s2, size_t n);
char		*ft_recover_variable(char *name, t_envir *envs);
int			ft_check(char *str, int i);

//free
void		ft_free_tab(char **str);
void		ft_free_tabcmd(t_tabcmd *tab);
void		ft_free_child(char *str, char **str2, t_envir *envs,
				t_tabcmd *tabcmd);
void		ft_free_exit(t_tabcmd *tab, t_envir *envs, char **str,
				t_pipe *pipes);
void		ft_free_parent(t_tabcmd *tab, char **str, char *str2);

//close
void		ft_close_fd(int fd1, int fd2, int fd3, int fd4);
void		ft_close_pipe(int fd1, int fd2);
void		ft_close_all_file(t_tabfile *tabfile, int nb_file);

char		**ft_split_quote(char *s, char c);
char		**ft_split_ws_quote(char *s);

//exec
int			exec(int nb_cmd, t_tabcmd *tabcmd, t_envir *envs);
int			open_file(t_tabcmd tabcmd, t_pipe *pipes);
int			is_builtins(char *cmd);
void		ft_builtins(t_tabcmd *tabcmd, t_envir *envs);	
char		*ft_path(char *cmd, char **env);
char		**ft_stock_cmd(char *cmd);	
int			ft_child(t_tabcmd *tabcmd, t_envir *envs, t_pipe *pipes, int i);
int			ft_child_builtins(t_tabcmd *tabcmd, t_envir *envs,
				t_pipe *pipes, int i);
void		exec_single_builtins(t_tabcmd *tabcmd, t_pipe *pipes,
				t_envir *envs);
char		*ft_replace_quote(char *str);

//builtins
void		ft_echo(char *arg);
void		ft_unset(t_tabcmd *tabcmd, t_envir *envs);
void		ft_envs(t_envir *envs);
void		ft_pwd(void);
void		ft_cd(t_tabcmd *tabcmd, t_envir *envs);
void		ft_exit(t_tabcmd *tabcmd, t_pipe *pipes, t_envir *envs, int j);

//export
void		ft_export(char *cmd, t_envir *envs);
int			check_export(char *arg);
int			check_if_already_in_env(t_envir *envs, char *name);
void		ft_print_export_quote(char *str);
char		**ft_realloc(char **tab, int pull);
void		ft_export_add_env(t_envir *envs, char *line);
void		ft_export_del_to_create(char *str, t_envir *envs,
				int start, char *name);
void		ft_export_arg(char *str, t_envir *envs);
void		ft_export_create_line(char *str, t_envir *envs,
				char *name, int start);
void		ft_export_append(char *name, char *str, int start, t_envir *envs);
int			ft_count(char *str, int i);

// signals
void		ctrl_c(int sig);
void		ctrl_c_heredoc(int sig);
void		signal_child(int sig);

#endif
