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

char **ft_realloc(char **old, int new_size)
{
    char **new;
    int i;

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

int is_valid_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == ' ');
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

static int	ft_len(char const *s, size_t len)
{
	size_t	i;

	i = 0;
	while (s[i] && i < len)
		i++;
	return (i);
}

int ft_split_len(char **split)
{
    int len = 0;

    while (split[len] != NULL)
        len++;
    return len;
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char) c)
			return ((char *) s + i);
		i++;
	}
	if (!c)
		return ((char *) s + i);
	return (NULL);
}

char	*ft_substr(char *s, size_t start, size_t len)
{
	char	*new_s;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	if (start >= ft_strlen_gnl(s))
		return (ft_strdup(""));
	new_s = (char *)malloc(ft_len(s + start, len) + 1 * sizeof(char));
	if (!new_s)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (start <= i && j < len)
		{
			new_s[j] = s[i];
			j++;
		}
		i++;
	}
	new_s[j] = '\0';
	return (new_s);
}

char	*ft_strdup(char *s)
{
	int		pos;
	char	*cpy;

	cpy = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!cpy)
		return (NULL);
	pos = 0;
	while (s[pos] != '\0')
	{
		cpy[pos] = s[pos];
		pos++;
	}
	cpy[pos] = '\0';
	return (cpy);
}

void free_split(char **split)
{
    int i;

    if (!split)
        return;

    i = 0;
    while (split[i] != NULL)
    {
        free(split[i]);
        i++;
    }
    free(split);
}

static size_t	count_word(char *s, char sep)
{
	size_t	nword;

	nword = 0;
	if (!s)
		return (0);
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			nword++;
		while (*s != sep && *s)
			s++;
	}
	return (nword);
}

static void	*ft_free(char **array, size_t i)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
	return (NULL);
}

static char	**ft_split2(char *s, char c, char **array)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!ft_strchr(s, c))
				len = ft_strlen(s);
			else
				len = ft_strchr(s, c) - s;
			array[i] = ft_substr(s, 0, len);
			if (!array[i])
				return (ft_free(array, i));
			i++;
			s += len;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	array = ft_split2(s, c, array);
	return (array);
}