#include "minishell.h"

int	g_exit;

static void	ctrl_d_main(t_envir *envs)
{
	ft_free_tab(envs->envi);
	free(envs);
	ft_putstr_fd("exit\n", 2);
	exit (g_exit);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_envir	*envs;

	(void)argv;
	g_exit = 0;
	if (argc != 1)
		return (1);
	envs = get_env(env);
	printf("Mimish Version 0.0.4.2\nPress Ctrl+d to Exit\n");
	while (1)
	{
		signal(SIGINT, &ctrl_c);
		signal(SIGQUIT, SIG_IGN);
		input = readline("mimish> ");
		if (!input)
			ctrl_d_main(envs);
		add_history(input);
		parse(input, envs);
	}
	return (0);
}
