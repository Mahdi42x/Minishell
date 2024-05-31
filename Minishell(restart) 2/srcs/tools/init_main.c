#include "../../includes/minishell.h"

void	init_minishel(t_minishell *minishell)
{
	minishell.in = dup(STDIN);
	minishell.out = dup(STDOUT);
	minishell.exit = 0;
	minishell.ret = 0;
	minishell.no_exec = 0;
	minishell.start = 0;
	minishell->charge = 1;
	minishell->parent = 1;
	minishell->last = 1;
}