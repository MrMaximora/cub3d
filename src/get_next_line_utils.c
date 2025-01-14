/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:20:39 by maxouvra          #+#    #+#             */
/*   Updated: 2024/01/25 13:43:59 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strcat(char *dest, char *src, char *f_str)
{
	size_t	pos;
	size_t	lendest;

	pos = 0;
	if (!dest)
		lendest = 0;
	else
	{
		lendest = ft_strlen_gnl(dest);
		while (dest[pos])
		{
			f_str[pos] = dest[pos];
			pos++;
		}
	}
	pos = 0;
	while (src[pos])
	{
		f_str[lendest + pos] = src[pos];
		pos++;
	}
	f_str[lendest + pos] = '\0';
	return (f_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	new_s_len;
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
		new_s_len = ft_strlen_gnl(s2) + 1;
	else
		new_s_len = ft_strlen_gnl(s1) + ft_strlen_gnl(s2) + 1;
	str = (char *)malloc(sizeof(*str) * new_s_len);
	if (!str)
		return (NULL);
	str = ft_strcat((char *)s1, (char *)s2, str);
	free(s1);
	return (str);
}

int	ft_atoi(char *str)
{
	int	pos;
	int	res;
	int	sign;

	pos = 0;
	res = 0;
	sign = 1;
	while (str[pos] == ' ' || (str[pos] >= 9 && str[pos] <= 13))
		pos++;
	if (str[pos] == '-' || str[pos] == '+')
	{
		if (str[pos] == '-')
			sign *= -1;
		pos++;
	}
	while (str[pos] >= '0' && str[pos] <= '9')
	{
		res = (res * 10) + (str[pos] - '0');
		pos++;
	}
	return (res * sign);
}
