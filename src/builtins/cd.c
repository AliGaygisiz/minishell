/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:46:47 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static void	update_cd(char *old_pwd, char *new_pwd)
{
	if (!export_change_data(old_pwd, equal_sign_index(old_pwd)))
	{
		update_export(old_pwd);
		add_env(old_pwd);
	}
	else if (!export_change_data(new_pwd, equal_sign_index(new_pwd)))
	{
		add_env(new_pwd);
		update_export(new_pwd);
	}
}

void	change_position(char *dir, char *pwd)
{
	char	*old_pwd;
	char	*new_pwd;
	char	buff[PATH_MAX];

	old_pwd = ft_strdup("OLDPWD=");
	old_pwd = ft_strjoin(old_pwd, pwd);
	new_pwd = ft_strdup("PWD=");
	if (ft_strlen(dir) + ft_strlen(pwd) > 1024)
		printf("%s\n", CD_ERROR);
	else if (chdir(dir) == -1)
	{
		g_data->return_value = 1;
		perror("cd");
	}
	else
	{
		new_pwd = ft_strjoin(new_pwd, getcwd(buff, PATH_MAX));
		update_cd(old_pwd, new_pwd);
		g_data->return_value = 0;
	}
	free(old_pwd);
	free(new_pwd);
}

static char	*tilde_path(char *command)
{
	char	*tilde_path;

	tilde_path = ft_strdup(ft_getenv("HOME", 0));
	if (tilde_path == NULL)
	{
		printf("HOME not set\n");
		return (NULL);
	}
	tilde_path = ft_strjoin(tilde_path, command + 1);
	return (tilde_path);
}

void	redirect_cd(char *dir, char *pwd)
{
	char	*tmp_path;

	if (dir[0] == '~' && dir[1] == '/')
	{
		tmp_path = tilde_path(dir);
		change_position(tmp_path, pwd);
		free(tmp_path);
	}
	else if (dir[0] == '~' && dir[1] == '\0')
	{
		tmp_path = ft_getenv("HOME", 0);
		change_position(tmp_path, pwd);
	}
	else if (dir[0] == '-' && dir[1] == '\0')
	{
		printf("%s\n", ft_getenv("OLDPWD", 0));
		change_position(ft_getenv("OLDPWD", 0), pwd);
	}
}

void	ft_cd(char **command)
{
	char	*tmp_path;
	char	*dir;
	char	*pwd;

	dir = command[1];
	pwd = ft_getenv("PWD", 0);
	if (dir == NULL)
	{
		tmp_path = ft_getenv("HOME", 0);
		if (tmp_path == NULL)
		{
			printf("cd: HOME not set");
			g_data->return_value = 1;
		}
		else
			change_position(tmp_path, pwd);
	}
	else if (dir[0] == '~' || dir[0] == '-')
		redirect_cd(dir, pwd);
	else
		change_position(dir, pwd);
}
