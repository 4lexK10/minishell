#include "parsing.h"

int main(int ac, char **av, char **envp)
{
	t_data *data = NULL;
	char *str = "$\"hi\" prout";

	(void)ac;
	(void) av;
	(void)envp;
	data = parsing(str, 1313, 0);
	if (!data)
		return (printf("Data = NULL\n"), 1);
	t_data *link = data;
	while (link)
	{
		printf("-%s\n", link->word);
		printf("token -> %d\n", link->token);
		link = link->next;
	}
	// int i = -1;
	// while (test[++i])
	// 	printf("env : %s\n", test[i]);
	// free_list(&data);
	// system("leaks a.out");
	return (0);
}
