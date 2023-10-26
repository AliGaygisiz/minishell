/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:37:27 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

void	close_pipe_fd(void)
{
	int	i;

	i = 0;
	while (i < g_data->pipe_count)
	{
		close(g_data->fd[i][0]);
		close(g_data->fd[i][1]);
		i++;
	}
	if (g_data->input_file > 2)
		close(g_data->input_file);
	if (g_data->output_file > 2)
		close(g_data->output_file);
}

void	pipe_counter(t_parse *lst)
{
	t_parse	*temp;

	temp = lst;
	while (temp != NULL)
	{
		if (!ft_strcmp(temp->content, "|"))
			g_data->pipe_count++;
		temp = temp->next;
	}
	if (g_data->pipe_count != 0)
	{
		g_data->fd = malloc(g_data->pipe_count * sizeof(int *));
		g_data->pid_array = malloc((g_data->pipe_count + 1) * sizeof(pid_t));
		g_data->rtn_arr = ft_calloc((g_data->pipe_count + 1), sizeof(int));
	}
}

void	create_pipe_fd(void)
{
	int	i;

	i = 0;
	while (i < g_data->pipe_count)
	{
		g_data->fd[i] = malloc(sizeof(int) * 2);
		pipe(g_data->fd[i]);
		i++;
	}
}

void	free_fd(void)
{
	int	i;

	i = 0;
	while (i < g_data->pipe_count)
	{
		free(g_data->fd[i]);
		i++;
	}
	free(g_data->fd);
	free(g_data->pid_array);
	free(g_data->rtn_arr);
}

char	**get_path(void)
{
	char	*temp;
	char	**path;
	int		i;

	i = 0;
	temp = ft_strdup(ft_getenv("PATH", 1));
	if (temp)
	{
		i = 0;
		while (temp[i] && temp[i] != '/')
			i++;
		path = libft_split((temp + i), ':');
		free(temp);
		return (path);
	}
	return (0);
}
