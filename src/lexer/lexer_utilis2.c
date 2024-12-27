/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utilis2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjniane <bjniane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 18:15:01 by bjniane           #+#    #+#             */
/*   Updated: 2024/11/18 23:46:29 by bjniane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_inside_qt(char c, int *singl, int *doubl)
{
	if (c == '\'' && *doubl != -1)
		*singl *= -1;
	if (c == '\"' && *singl != -1)
		*doubl *= -1;
	if ((is_whitespace(c) || is_special(c) || special_char(c)) && (*singl != -1
			&& *doubl != -1))
		return (0);
	else
		return (1);
}

void	handle_word(t_token **token, char *str, int *i)
{
	char	*word;
	int		start;
	int		sing;
	int		doub;

	sing = 1;
	doub = 1;
	start = *i;
	while (str[*i] && ft_inside_qt(str[*i], &sing, &doub))
		(*i)++;
	word = ft_substr(str, start, *i - start);
	ft_lstadd_back(token, ft_lstnew(word, WORD));
}

void	handle_pipe(t_token **token, char *str, int *i)
{
	if (str[*i] == '|')
	{
		if (str[*i + 1] == '|')
		{
			ft_lstadd_back(token, ft_lstnew("||", OR));
			(*i)++;
		}
		else
			ft_lstadd_back(token, ft_lstnew("|", PIPE));
	}
}

void	handle_special(t_token **token, char *str, int *i)
{
	if (str[*i] == '|')
	{
		if (str[*i + 1] == '|')
		{
			ft_lstadd_back(token, ft_lstnew("||", OR));
			(*i)++;
		}
		else
			ft_lstadd_back(token, ft_lstnew("|", PIPE));
	}
}

void	handle_redirection(t_token **token, char *str, int *i)
{
	if (str[*i] == '<')
	{
		if (str[*i + 1] == '<')
		{
			ft_lstadd_back(token, ft_lstnew("<<", HERDOC));
			(*i)++;
		}
		else
			ft_lstadd_back(token, ft_lstnew("<", REDIR_IN));
	}
	else if (str[*i] == '>')
	{
		if (str[*i + 1] == '>')
		{
			ft_lstadd_back(token, ft_lstnew(">>", APPEND));
			(*i)++;
		}
		else
			ft_lstadd_back(token, ft_lstnew(">", REDIR_OUT));
	}
}
