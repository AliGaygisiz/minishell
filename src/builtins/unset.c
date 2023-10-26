/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 05:02:03 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static void	unset_env(char *var_name)
{
	int		i;
	char	**env;

	env = g_data->envp;
	i = 0;
	while (env[i] != NULL)
	{
		if (!is_env_eq(var_name, env[i]))
		{
			free(env[i]);
			while (env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

static void	unset_export(char *var_name)
{
	int		i;
	char	**export;

	i = 0;
	export = g_data->export;
	while (export[i] != NULL)
	{
		if (!is_export_eq(var_name, export[i]))
		{
			free(export[i]);
			while (export[i] != NULL)
			{
				export[i] = export[i + 1];
				i++;
			}
			break ;
		}
		i++;
	}
}

void	ft_unset(char **var_names)
{
	int	i;

	i = 1;
	while (var_names[i])
	{
		unset_env(var_names[i]);
		unset_export(var_names[i]);
		i++;
	}
	g_data->return_value = 0;
}
