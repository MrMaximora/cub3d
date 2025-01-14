/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <maxouvra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:56:24 by maxouvra          #+#    #+#             */
/*   Updated: 2024/11/14 10:56:25 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnstr(char *str, char *to_find, int len)
{
	int	pos;
	int	find;

	pos = 0;
	if (ft_strlen(to_find) == 0)
		return (str);
	while (pos < len && str[pos])
	{
		find = 0;
		while (str[pos + find] == to_find[find] && str[pos + find] \
			&& (pos + find) < len)
		{
			find++;
		}
		if (to_find[find] == '\0' && str[pos + find] == '\0')
			return (&str[pos]);
		pos++;
	}
	return (NULL);
}

char	**ft_realloc(char **old, int new_size)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(new_size * sizeof(char *));
	if (!new)
		return (NULL);
	if (old)
	{
		while (old[i] && i < new_size)
		{
			new[i] = old[i];
			i++;
		}
		free(old);
	}
	while (i < new_size)
	{
		new[i] = NULL;
		i++;
	}
	return (new);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || \
		c == 'W' || c == ' ');
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	pos;

	pos = 0;
	if (n == 0)
		return (0);
	while ((s1[pos] == s2[pos]) && (s1[pos] && s2[pos]) && pos < n - 1)
	{
		pos++;
	}
	return (s1[pos] - s2[pos]);
}
