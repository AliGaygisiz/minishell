/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_command_execute.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:38:03 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static void	manipulate_fd(int i)
{
	if (i == 0)
		dup2(g_data->fd[i][STDOUT_FILENO], STDOUT_FILENO);
	else if (i == g_data->pipe_count)
		dup2(g_data->fd[i - 1][0], 0);
	else
	{
		dup2(g_data->fd[i - 1][0], 0);
		dup2(g_data->fd[i][1], 1);
	}
	if (g_data->input_file > 2)
	{
		dup2(g_data->input_file, 0);
		close(g_data->input_file);
	}
	if (g_data->output_file > 2)
	{
		dup2(g_data->output_file, 1);
		close(g_data->output_file);
	}
}

static void	ft_execute(char *abs_path, char **command, int index, int builtin)
{
	if (abs_path || !builtin)
	{
		g_data->state_flag = COMMAND;
		g_data->pid_array[index] = fork();
		if (g_data->pid_array[index] == CHILD)
		{
			manipulate_fd(index);
			close_pipe_fd();
			if (!builtin)
				nav_builtin(command);
			else if (g_data->input_file != -1)
				execve(abs_path, command, g_data->envp);
			exit(1);
		}
	}
	else if (chardb_len(command) != 0)
	{
		printf("minishell: %s: command not found\n", command[0]);
		g_data->rtn_arr[index] = 127;
	}
}

void	wait_child(void)
{
	int	i;
	int	child_exit_status;
	int	prev_cmd_ret;

	i = 0;
	prev_cmd_ret = -1;
	while (i < g_data->pipe_count + 1)
	{
		if (g_data->pid_array[i] != -1)
		{
			waitpid(g_data->pid_array[i], &g_data->return_value, 0);
			if (WIFEXITED(g_data->return_value))
			{
				child_exit_status = WEXITSTATUS(g_data->return_value);
				if (child_exit_status == 127)
					g_data->rtn_arr[i] = 127;
				else if (child_exit_status == 1)
					g_data->rtn_arr[i] = 1;
				else if (prev_cmd_ret == 127 || prev_cmd_ret == 1)
					g_data->rtn_arr[i] = 0;
				prev_cmd_ret = child_exit_status;
			}
		}
		i++;
	}
}

static void	command_check(char **command, char *abs_path, int builtin, int *i)
{
	if (command[0])
	{
		delete_quote(command);
		builtin = builtin_check(command[0]);
		if (builtin && ft_strlen(command[0]) != 0)
			abs_path = find_path(command[0]);
		ft_execute(abs_path, command, *i, builtin);
		if (abs_path)
			free(abs_path);
		(*i)++;
	}
}

void	multi_command_execute(t_parse *lst)
{
	char	**command;
	char	*abs_path;
	int		i;
	int		builtin;

	i = 0;
	builtin = 0;
	abs_path = NULL;
	while (lst != NULL)
	{
		g_data->input_file = -2;
		g_data->output_file = -2;
		if (ft_strcmp(lst->content, "|"))
		{
			command = nav_redirection(lst->content, 0);
			command_check(command, abs_path, builtin, &i);
			free_command_db(command);
			free(abs_path);
		}
		lst = lst->next;
	}
	close_pipe_fd();
	wait_child();
	g_data->return_value = g_data->rtn_arr[g_data->pipe_count];
}
