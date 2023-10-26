/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:11:59 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:07:04 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static void	check_heredoc(char *temp)
{
	int	i;

	if (strrchar(temp, '<') != 0 && g_data->input_file != -1)
	{
		i = strrchar(temp, '<');
		if (i > 0 && temp[i - 1] == '<')
			change_data_input(open("heredoc", O_RDWR | O_APPEND, 0777));
	}
}

char	**nav_redirection(char *content, int i)
{
	char	**rtn_arr;
	char	*temp;

	temp = ft_strdup(content);
	while (temp[i] && g_data->input_file != -1)
	{
		if (temp[i] == '\'')
			i += strchar(&temp[i + 1], '\'') + 2;
		else if (temp[i] == '"')
			i += strchar(&temp[i + 1], '"') + 2;
		else if (temp[i] == '<')
			i = input_redirection(temp, ++i);
		else if (temp[i] == '>' && temp[i + 1] == '>')
			i = append_redirection(temp, i + 2);
		else if (temp[i] == '>' && temp[i + 1] != '>')
			i = output_redirection(temp, ++i);
		else if (temp[i])
			i++;
	}
	check_heredoc(temp);
	temp = remove_redirection(temp, 0);
	rtn_arr = libft_split(temp, 32);
	free(temp);
	return (rtn_arr);
}

static int	remove_append(char *str, int i)
{
	if (str[i] == '\'')
		i += strchar(&str[i + 1], '\'') + 2;
	if (str[i] == '"')
		i += strchar(&str[i + 1], '"') + 2;
	else
		i++;
	return (i);
}

void	skip_file_name(char *str, int *i)
{
	int	flag;

	flag = 0;
	while (str[(*i)] == 32 || str[(*i)] == '<' || str[(*i)] == '>')
		(*i)++;
	if (str[(*i)] == '\"' || str[(*i)] == '\'')
	{
		flag = 1;
		(*i)++;
	}
	while (str[(*i)] && (str[(*i)] != 32 || flag == 1))
	{
		if (str[(*i)] && str[(*i)] == 32 && \
			(str[(*i)] == '\"' || str[(*i)] == '\''))
			flag = 0;
		(*i)++;
	}
}

char	*remove_redirection(char *str, char *new)
{
	int	i;
	int	n;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == 32)
			i++;
		if (str[i] == '<' || str[i] == '>')
			skip_file_name(str, &i);
		else if (str[i])
		{
			n = i;
			while (str[i] && str[i] != '<' && str[i] != '>')
				i = remove_append(str, i);
			new = s2_strjoin(new, substr(str, n, i - n));
		}
	}
	free(str);
	return (new);
}
