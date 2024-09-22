#include "parsing.h"

int main(int ac, char **av, char **envp)
{
	// t_data *data = NULL;
	char *str;
	int	flag;

	(void)ac;
	(void)av;
	flag = 0;
	if (check_our_env("PAGER", &str, envp, &flag) == 0)
		return (1);
	printf("str = %s\n", str);
	// data = parsing(str, 1313, 0);
	// if (!data)
	// 	return (printf("Data = NULL\n"), 1);
	// t_data *link = data;
	// while (link)
	// {
	// 	printf("-%s\n", link->word);
	// 	printf("token -> %d\n", link->token);
	// 	link = link->next;
	// }
	int i = -1;
	while (envp[++i])
		printf("env : %s\n", envp[i]);
	// free_list(&data);
	// system("leaks a.out");
	return (0);
}
