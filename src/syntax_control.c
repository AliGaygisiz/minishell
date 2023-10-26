/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_control.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:47:20 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:15:47 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

t_data	*g_data;

static int	pipe_space(t_parse *temp)
{
	int	i;

	i = 0;
	if (temp->next != NULL && temp->next->content[0] == '|')
	{
		while (temp->content[i] && temp->content[i] == 32)
			i++;
		if (temp->content[i] == 0)
			return (1);
	}
	return (0);
}

void	syntax_check(t_parse *parse)
{
	t_parse	*temp;

	temp = parse;
	while (temp != NULL && g_data->syntax_flag == 0)
	{
		if (pipe_space(temp))
			g_data->syntax_flag = 1;
		else if (multiple_pipes(temp))
			g_data->syntax_flag = 1;
		else if (strmatch(temp->content, "<>"))
			pre_trim(temp->content);
		temp = temp->next;
	}
}

int	multiple_pipes(t_parse *temp)
{
	int	i;

	i = 0;
	if (temp->next != NULL && temp->content[0] == '|')
	{
		if (temp->next->content[0] == '|')
			return (1);
		while (temp->next->content[i] && temp->next->content[i] == 32)
			i++;
		if (temp->next->content[i] == 0)
			return (1);
	}
	else if (temp->content[0] == '|' && temp->next == NULL)
		return (1);
	else
		return (0);
	return (0);
}

void	pre_trim(char *find)
{
	int	i;

	i = 0;
	while (find[i] && g_data->syntax_flag == 0)
	{
		if (find[i] == '\'')
			i += strchar(&find[i + 1], '\'') + 2;
		else if (find[i] == '"')
			i += strchar(&(find[i + 1]), '"') + 2;
		else if (find[i] == '<')
			syntax_redirection(find, '<', &i, 0);
		else if (find[i] == '>')
			syntax_redirection(find, '>', &i, 0);
		if (find[i])
			i++;
	}
}

int	syntax_redirection(char *str, char symbol, int *i, int flag)
{
	char	rev_sym;

	if (symbol == '<')
		rev_sym = '>';
	else
		rev_sym = '<';
	if (str[(*i)] != 0 && str[(*i)] == symbol)
	{
		(*i)++;
		if (str[(*i)] == '\0' || str[(*i)] == rev_sym)
			g_data->syntax_flag = 1;
		if (str[(*i)] == symbol && g_data->syntax_flag == 0)
		{
			if (symbol == '<')
				flag = 1;
			(*i)++;
		}
		while (str[(*i)] && str[(*i)] == 32)
			(*i)++;
		if (str[(*i)] == '\0' || str[(*i)] == symbol || str[(*i)] == rev_sym)
			g_data->syntax_flag = 1;
		if (flag == 1 && g_data->syntax_flag == 0)
			g_data->heredoc_cnt++;
	}
	return (0);
}
