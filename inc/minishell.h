#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "minishell.h"


# define PATH_MAX 4096

# define SUCCESS 0
# define FAILURE -1
# define HANDLED -2

# define NAFD -2

# define IN_HEREDOC 2
# define AFTER_HEREDOC 3
# define IN_CMD 4
# define AFTER_CMD 5

# define ENO_OTHER 40000

# define ERR_NO_SUCH_FILE_OR_DIR 30002
# define ERR_NUMERIC_ARG_REQUIRED 30003
# define ERR_TOO_MANY_ARG 30004
# define ERR_NOT_A_VALID_IDENTIFIER 30005
# define ERR_PERMISSION_DENIED 30006
# define ERR_PERMISSION_DENIED_BROKEN_PIPE 30007
# define ERR_IS_DIR 30008

# define ERR_HOME_NOT_SET 10001
# define ERR_CMD_NOT_FOUND 10002
# define ERR_CANT_CHANGE_DIR 10003
# define ERRP_NOT_A_VALID_IDENTIFIER 10004
# define ERR_NOT_VALID_IN_THIS_CTX 10005

# define ENDL "\n"
# define ESTR_UNKNOWN "unknown error"
# define ESTR_UNEXPECTED "unexpected error"
# define ESTR_CMD_NOT_FOUND "command not found"
# define ESTR_HOME_NOT_SET "HOME not set"
# define ESTR_CANT_CHANGE_DIR "cannot change directory"
# define ESTR_INVALID_ARG "invalid argument"
# define ESTR_NOT_A_VALID_IDENTIFIER "not a valid identifier"
# define ESTR_NO_SUCH_FILE_OR_DIR "no such file or directory"
# define ESTR_NUMERIC_ARG_REQUIRED "numeric argument required"
# define ESTR_TOO_MANY_ARG "too many arguments"
# define ESTR_PERMISSION_DENIED "permission denied"
# define ESTR_PERMISSION_DENIED_BROKEN_PIPE "permission denied"
# define ESTR_IS_DIR "is a directory"
# define ESTR_NOT_VALID_IN_THIS_CTX "not valid in this context"
# define ESTR_SYN_UNKNOWN_ERR "unknown syntax error"
# define ESTR_SYN_ZERO_PIPE "syntax error near unexpected token `newline'"
# define ESTR_SYN_EMPTY_AFTER "syntax error near unexpected token `newline'"
# define ESTR_SYN_MISS_QUOTE "unexpected quote `'', `\"'"

# define COLOR_RED "\e[0;31m"
# define COLOR_GREEN "\e[0;32m"
# define COLOR_RESET "\e[0m"

# define PROMPT "minishell: "

extern int			g_sig;

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
	struct s_env		*prev;
}	t_env;

typedef struct s_syntax
{
	unsigned char	duplex;
	unsigned char	simplex;
	unsigned char	zero_pipe;
	unsigned char	undefined;
}					t_syntax;

typedef enum e_token_type
{
	NONE,
	CMD,
	ARG,
	PIPE,
	RED_L,
	RED_LL,
	RED_R,
	RED_RR,
	RED_FILE,
	RED_HEREDOC
}					t_token_type;

typedef struct s_token
{
	char			*data;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_token_append_meta_data
{
	t_token_type	type;
	int				in_quote;
	bool			has_meta;
	int				i;
	int				start;
}					t_token_append_meta_data;

typedef struct s_token_sep_md
{
	t_token			**token_arr;
	t_token			*iter;
	t_token			*temp;
	t_token			*temp_root;
	int				i;
}					t_token_sep_md;

typedef struct s_state
{
	int				status;
	char			**argv;
	char			**env;
	char			*prompt;
	t_token			**token_arr;
	int				cmd_ct;
	int				err;
}					t_state;

typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	int				in;
	int				out;
	int				*heredoc;
	int				idx;
	int				count;
	int				bin;
	int				bout;
}					t_cmd;

int		main(int ac, char **av, char **env);
int		syntax_cont(char *input);
t_env	**envfunc(char	**env, int n);
char	*funcval(char	*env, int start);
char	*funckey(char	*env, int end);
t_env	**lstadd_back(t_env **lst, t_env *new, int n);
void	run_cmds(char *input, char **env);

#endif

