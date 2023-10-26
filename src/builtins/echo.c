/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 18:21:50 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:47:39 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

static int	check_flag(char *command)
{
	int	i;

	i = 0;
	if (!command || command[0] != '-')
		return (0);
	while (command[++i])
	{
		if (command[i] != 'n')
			return (0);
	}
	return (1);
}

void	echo_mini(char **command, int i)
{
	write(1, command[i], ft_strlen(command[i]));
	if (command[i + 1] != 0)
		write(1, " ", 1);
	i++;
}

void	ft_echo(char **command)
{
	int	i;
	int	check;

	check = 0;
	i = 1;
	if (!command[1])
	{
		printf("\n");
		return ;
	}
	if (command[1])
		check = check_flag(command[1]);
	if (check == 1)
		i = 2;
	if (!command[i])
		return ;
	while (command[i])
	{
		echo_mini(command, i);
		i++;
	}
	if (check == 0)
		printf("\n");
	g_data->return_value = 0;
}
