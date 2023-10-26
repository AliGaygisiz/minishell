/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkiziler <bkiziler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 17:35:38 by bkiziler          #+#    #+#             */
/*   Updated: 2023/10/26 04:06:28 by bkiziler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lib.h"

t_data	*g_data;

int	search(char *detect, char *found)
{
	int	i;
	int	a;

	i = -1;
	while (detect[++i])
	{
		a = 0;
		while (detect[i] && found[a] && detect[i] == found[a])
		{
			i++;
			a++;
		}
		if (found[a] == '\0')
			return (1);
	}
	return (0);
}

int	strrchar(char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	while (len >= 0)
	{
		if (s[len] == (char)c)
			return (len);
		len--;
	}
	return (-1);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (0);
	i = 0;
	while (i < n)
	{
		*(char *)(dest + i) = *(char *)(src + i);
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	char	*dup;

	dup = malloc(ft_strlen(s1) * sizeof(char) + 1);
	if (!dup)
		return (0);
	ft_memcpy(dup, s1, ft_strlen(s1));
	dup[ft_strlen(s1)] = '\0';
	return (dup);
}

void	change_data_input(int file)
{
	if (g_data->input_file == -1 || file == -1)
	{
		printf("No such file or directory\n");
		g_data->return_value = 1;
	}
	if (g_data->input_file >= 0)
		close(g_data->input_file);
	g_data->input_file = file;
}
