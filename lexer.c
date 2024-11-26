/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmarijan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:22:03 by dmarijan          #+#    #+#             */
/*   Updated: 2024/11/26 13:33:04 by dmarijan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/minishell.h"

int	expand_list(char *str, t_tokens token, t_msh *mini, int *end)
{
	if (str && *str)
		append_node(&mini->list, str, 0, mini);
	if (token != 0)
		append_node(&mini->list, NULL, token, mini);
	if (token == LLESS || token == GGREAT)
		*end = *end + 1;
	return (*end);
}

char	plumbus(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (istoken(str, i))
		return (str[i]);
	while (str[i])
	{
		if (istoken(str, i))
		{
			i += istoken(str, i);
			while (ft_isspace(str[i]))
				i++;
			if (!str[i])
				return ('\n');
			else if (istoken(str, i))
				return (str[i]);
		}
		i++;
	}
	return (0);
}

int	quote_lexer(t_msh *mini, int end, char *str)
{
	int		nquote;
	char	quote;

	quote = 0;
	nquote = 0;
	while (str[end] && end < (int)ft_strlen(str) && str[end] != quote)
	{
		if (str[end] == '\"' || str[end] == '\'')
		{
			quote = str[end];
			nquote++;
			end++;
			while (str[end] && str[end] != quote)
				end++;
			if (!str[end])
				return (0);
			nquote++;
		}
		if (str[end] && str[end] != quote)
			end++;
	}
	if (nquote % 2)
		return (0);
	return (end);
}

static void	if_shrimpin_then_lexin(int *e, int *stt, char *str, t_msh *msh)
{
	if (str[*e] == '\"' || str[*e] == '\'')
	{
		*e = quote_lexer(msh, *e, msh->args);
		if (!*e)
			errexit(msh, "syntax error: unclosed quotes!\n");
	}
	if (str[*e] == '|')
		*stt = expand_list(ft_substr(str, *stt, *e - *stt), PIPE, msh, e) + 1;
	else if (str[*e] == '<' && !isdouble(str + *e, 0))
		*stt = expand_list(ft_substr(str, *stt, *e - *stt), LESS, msh, e) + 1;
	else if (str[*e] == '>' && !isdouble(str + *e, 1))
		*stt = expand_list(ft_substr(str, *stt, *e - *stt), GREAT, msh, e) + 1;
	else if (str[*e] == '<' && isdouble(str + *e, 0))
		*stt = expand_list(ft_substr(str, *stt, *e - *stt), LLESS, msh, e) + 2;
	else if (str[*e] == '>' && isdouble(str + *e, 1))
		*stt = expand_list(ft_substr(str, *stt, *e - *stt), GGREAT, msh, e) + 2;
	else if (!str[*e + 1])
		*stt = expand_list(ft_substr(str, *stt, *e - *stt + 1), 0, msh, e);
}

void	shrimp_lexer(t_msh *mini)
{
	int		stt;
	int		end;
	char	*str;
	char	tmp;

	str = mini->args;
	stt = 0;
	end = -1;
	if (istheretokens(str))
	{
		tmp = plumbus(str);
		if (tmp)
		{
			if (tmp == '\n')
				ft_printf(2, "msh: syntax error near unexpected 'newline'.\n");
			else
				ft_printf(2, "msh: syntax error near unexpected '%c'.\n", tmp);
			mini->returnval = 2;
			return ;
		}
	}
	while (str && ++end < (int)ft_strlen(str))
		if_shrimpin_then_lexin(&end, &stt, str, mini);
}
