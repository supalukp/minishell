# Structures

typedef enum e_type
{
	CMD,
	AGR
}			t_type;

typedef struct s_token
{
	char			*name;
	t_type			type;
	struct s_token	*next;
}

typedef struct s_branch
{
	t_token		*first_token;
	struct s_branch		*next;
	int					rank;
}				t_branch;

typedef struct	s_program
{
	int					branch_count;
	struct t_branch		*first_branch;

	// Information
	int 				pipes;
	int					and;
	int					or;
	int					here_doc;
	int					append;

	// Addresses
	char 				*infile_name;
	char				*outfile_name;
}				t_prog;