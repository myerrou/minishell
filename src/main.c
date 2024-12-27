/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myerrou <myerrou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 05:57:10 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/28 11:08:47 by myerrou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_sig	g_sig;

int	handle_quotes(char *str)
{
	int	sinqt;
	int	dbqot;
	int	i;

	sinqt = 1;
	dbqot = 1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && dbqot == 1)
			sinqt *= -1;
		if (str[i] == '\"' && sinqt == 1)
			dbqot *= -1;
		i++;
	}
	if (sinqt == -1 || dbqot == -1)
		return (0);
	return (1);
}

void	init_shell(char **env, t_env **envp)
{
	signal(SIGQUIT, SIG_IGN);
	*envp = env_init(*envp, env);
	increment_shell_level(*envp);
}

void	inside_loop(char *input, t_token *token, t_node *parsed, t_env *envp)
{
	token = ft_lexer(input);
	free(input);
	parsed = parsing(&token, envp);
	if (g_sig.execute != 1)
		execution(parsed, envp);
	if (g_sig.exit_status == 130 && g_sig.execute != 1)
		printf("\n");
	if (g_sig.exit_status == 131)
		printf("Quit: (core dumped)\n");
	g_sig.execute = 0;
}

void	shel_loop(t_env *envp)
{
	char	*input;
	t_token	*token;
	t_node	*parsed;

	token = NULL;
	parsed = NULL;
	while (1)
	{
		g_sig.flag = 0;
		signal(SIGINT, ft_signal);
		input = readline("minishell$ ");
		if (!input)
			break ;
		add_history(input);
		if (!handle_quotes(input))
		{
			free(input);
			g_sig.exit_status = 1;
			printf("Syntax error unclosed quote\n");
			continue ;
		}
		inside_loop(input, token, parsed, envp);
	}
	rl_clear_history();
	printf("exit\n");
}

int	main(int ac, char **av, char **env)
{
	t_env	*envp;

	envp = NULL;
	if (ac > 1)
		return (printf("minishell: %s: No such file or directory\n", av[1]), 1);
	init_shell(env, &envp);
	shel_loop(envp);
	free_trash();
	exit(g_sig.exit_status);
}
