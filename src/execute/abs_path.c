/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:32:49 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static char	*try_accses(char *command)
{
	int		i;
	char	*abs_path;
	char	*temp1;
	char	*temp2;

	i = -1;
	while (g_data->path[++i] != 0)
	{
		temp1 = ft_strdup(g_data->path[i]);
		temp2 = ft_strjoin(temp1, "/");
		abs_path = ft_strjoin(temp2, command);
		if (access(abs_path, F_OK) != -1)
		{
			free_command_db(g_data->path);
			return (abs_path);
		}
		free(abs_path);
	}
	return (0);
}

static char	*relative_path(char *command)
{
	char	*abs_path;
	char	*current_dir;

	current_dir = malloc(PATH_MAX * 1);
	current_dir = getcwd(current_dir, PATH_MAX);
	abs_path = ft_strjoin(current_dir, "/");
	current_dir = ft_strjoin(abs_path, command + 2);
	if (access(current_dir, F_OK) != -1)
	{
		free_command_db(g_data->path);
		return (current_dir);
	}
	free_command_db(g_data->path);
	free(current_dir);
	return (0);
}

static char	*tilde_path(char *command)
{
	char	*tilde_path;

	tilde_path = ft_strdup(ft_getenv("HOME", 0));
	if (tilde_path == NULL)
	{
		printf("HOME not set\n");
		free_command_db(g_data->path);
		return (NULL);
	}
	tilde_path = ft_strjoin(tilde_path, command + 1);
	free_command_db(g_data->path);
	printf("tilde_path -: %s\n", tilde_path);
	return (tilde_path);
}

char	*find_path(char *command)
{
	char	*abs_path;

	g_data->path = get_path();
	if (command[0] == '/' && access(command, F_OK) != -1)
	{
		free_command_db(g_data->path);
		return (ft_strdup(command));
	}
	else if (command[0] == '/')
	{
		free_command_db(g_data->path);
		return (NULL);
	}
	if (command[0] == '.' && command[1] == '/')
		return (relative_path(command));
	if (command[0] == '~')
		return (tilde_path(command));
	if (!g_data->path)
		return (NULL);
	abs_path = try_accses(command);
	if (abs_path)
		return (abs_path);
	free_command_db(g_data->path);
	return (0);
}
