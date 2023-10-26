/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 16:15:08 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:04:39 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

void	heredoc_list(t_parse *parse)
{
	g_data->state_flag = HEREDOC;
	while (parse != NULL)
	{
		if (search(parse->content, "<<") && g_data->heredoc_cnt > 0)
			heredoc_str(parse->content);
		parse = parse->next;
	}
	g_data->state_flag = READLINE;
}

void	heredoc_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i] && g_data->heredoc_cnt > 0 && g_data->signals != 1)
	{
		if (str[i] == '\'')
			i += strchar(&str[i + 1], '\'') + 2;
		else if (str[i] == '"')
			i += strchar(&str[i + 1], '"') + 2;
		else if (str[i] == '<' && str[i + 1] == '<')
			i = heredoc_file(str, i + 2) - 1;
	}
}

void	interrupt_here_document(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	exit (1);
}

static void	heredoc_addition(char *str, int i, int fd)
{
	char	*check;
	char	*take;

	check = trim_quote(str, i);
	if (fork() == 0)
	{
		signal(SIGINT, interrupt_here_document);
		take = readline("heredoc >>");
		while (ft_strcmp(take, check))
		{
			if (!take)
				exit(1);
			ft_putendl_fd(take, fd);
			free(take);
			take = readline("heredoc >>");
		}
		free(take);
		free(check);
		close(fd);
		exit (0);
	}
	else
		free(check);
	waitpid(-1, &g_data->return_value, 0);
}

int	heredoc_file(char *str, int i)
{
	int		fd;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (str[i] == 32)
		i++;
	heredoc_addition(str, i, fd);
	close(fd);
	change_data_input(open("heredoc", O_RDWR | O_APPEND, 0777));
	g_data->heredoc_cnt--;
	return (i);
}
