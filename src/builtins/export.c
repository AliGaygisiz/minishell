/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 05:34:56 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static void	print_export_line(char *export_line)
{
	int		eq_index;
	char	*temp;
	char	*var_name;
	char	*var_value;

	eq_index = equal_sign_index(export_line);
	if (eq_index == 0)
		printf("declare -x %s\n", export_line);
	else
	{
		temp = ft_strdup("declare -x ");
		var_name = ft_substr(export_line, 0, eq_index + 1);
		temp = ft_strjoin(temp, var_name);
		temp = ft_strjoin(temp, "\"");
		var_value = ft_substr(export_line, eq_index + 1, \
		ft_strlen(export_line) - eq_index);
		temp = ft_strjoin(temp, var_value);
		temp = ft_strjoin(temp, "\"");
		printf("%s\n", temp);
		free(temp);
		free(var_name);
		free(var_value);
	}
}

void	write_export(void)
{
	int	i;

	i = -1;
	while (g_data->export[++i])
		print_export_line(g_data->export[i]);
}

void	ft_export(char **export_cmd)
{
	int		equals_check;
	int		i;

	i = 1;
	while (export_cmd[i])
	{
		equals_check = equal_sign_index(export_cmd[i]);
		if (equals_check == -1)
		{
			i++;
			continue ;
		}
		else if (equals_check != -1)
		{
			if (!export_change_data(export_cmd[i], equals_check))
			{
				update_export(export_cmd[i]);
				sort_export();
				if (equals_check != 0)
					add_env(export_cmd[i]);
			}
		}
		i++;
	}
	g_data->return_value = 0;
}
