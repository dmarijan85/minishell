/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:43 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/23 17:52:09 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# include "libft/libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/libft/get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>

//Enums

typedef enum s_tokens
{
	PIPE = 1,
	GREAT,
	GGREAT,
	LESS,
	LLESS,
}				t_tokens;

typedef enum s_openmodes
{
	READ = 0,
	TRUNC,
	APPEND,
}			t_openmodes;

//Structs

typedef struct	s_redirs
{
	t_openmodes		fd_type;
	int				fd;
	struct s_redirs	*next;
	struct s_msh	*mini;
}				t_redirs;

typedef struct s_node
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_redirs	*redir;
	struct s_msh	*mini;
}				t_node;

typedef struct	s_msh
{
	char	**env;
	t_node	*list;
	char	*args;
	bool	reset;
	int		herectr;
	int		pipelen;
	int		exit;
}				t_msh;

//Prototypes

//main
void	minishell_loop(t_msh *mini);

//cleaners
void	stack_free_nodes(t_node **stack);
void	stack_free_redirs(t_redirs **stack);
void	node_free(t_node **stack);
void	array_free(char **str);
void	el_fregading(t_msh *mini);

//wordsplit
int		count_words(const char *str);
char	**wordsplit(char const *s);

//nodestuff
void	delete_node(t_node **node);

//parser
void	parser(t_msh *msh);

//lexer
void	shrimp_lexer(t_msh *mini);
void	append_redirs(t_redirs **stack, int fd, t_openmodes type, t_msh *mini);

//utils
int		fl_redir(t_redirs *current, t_openmodes mode);
void	remove_redir(t_msh *msh, t_node *node);
void	removequotes(char **str);

//utils two
void	do_last(t_msh *mini, char *cmd, char **env);
int		open_file(t_msh *mini, char *file, t_openmodes mode);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);

//utils three
int	ft_argc(char **argv);
int	ft_nodesize(t_node *lst);

//bomboclaat
void	lebomboclaat(t_msh *mini);
void	exec(t_msh *mini, char *cmd, char **env);
void	here_doc(t_msh *mini, t_node *node);

//donepezilo
void	reset_msh(t_msh *mini);
void	errexit(t_msh *mini, char *str);
void	childexit(t_msh *mini, char *str);

//builtins
void	ft_builtins(t_msh *mini, char **arr);
void	ft_exit(t_msh *mini, char **arr);
void	ft_env(char **envp);

#endif
