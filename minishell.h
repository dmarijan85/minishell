/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:43 by dmarijan          #+#    #+#             */
/*   Updated: 2024/10/14 12:51:26 by mclaver-         ###   ########.fr       */
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
# include "libft/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
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
}				t_redirs;

typedef struct s_node
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_node	*next;
	struct s_node	*prev;
	struct s_redirs	*redir;
}				t_node;

typedef struct	s_msh
{
	char	**env;
	t_node	*list;
	char	*args;
	bool	reset;
	int		herectr;
	int		listlen;
}				t_msh;

//Prototypes

//TODO:sort this shit pls
void	exit_handler(int n_exit);
int		open_file(char *file, t_openmodes mode);
char	*my_getenv(char *name, char **env);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	ft_free_tab(char **tab);
void	lexer(char *str, t_node **beg);
void	append_redirs(t_redirs **stack, int fd, t_openmodes type);

//cleaners
void	stack_free_nodes(t_node **stack);
void	stack_free_redirs(t_redirs **stack);
void	node_free(t_node **stack);
void	array_free(char **str);
void	remove_redir(t_node *node);

//wordsplit
int		count_words(const char *str);
char	**wordsplit(char const *s);

//nodestuff
void	delete_node(t_node **node);

//parser
void	parser(t_msh *msh);

#endif
