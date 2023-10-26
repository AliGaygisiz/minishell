/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:13:39 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/lib.h"

t_data	*g_data;

static int	check_line(void)
{
	if (g_data->line && *(g_data->line))
	{
		add_history(g_data->line);
		if (space_check(g_data->line))
			return (-1);
		parser();
		syntax_check(g_data->parse);
		if (g_data->syntax_flag == 1 && g_data->heredoc_cnt == 0)
		{
			printf("Syntax error\n");
			return (-1);
		}
		heredoc_list(g_data->parse);
		if (g_data->syntax_flag == 1)
		{
			printf("Syntax error\n");
			return (-1);
		}
		if (g_data->syntax_flag == 0)
			nav_execute();
		return (1);
	}
	else
		return (0);
}

void	reading_line(void)
{
	while (1)
	{
		g_data->state_flag = READLINE;
		g_data->line = readline("minishell > ");
		if (!g_data->line)
		{
			printf("exit\n");
			exit (1);
		}
		if (check_line() != 0)
			re_free();
		else
			free(g_data->line);
	}
}
