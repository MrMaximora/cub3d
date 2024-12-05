/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxouvra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 16:17:50 by maxouvra          #+#    #+#             */
/*   Updated: 2024/01/25 13:40:41 by maxouvra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static char	*write_new_line(char *line)
{
	int		i;
	int		j;
	char	*buff_line;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\n')
		i++;
	buff_line = malloc(sizeof(char) * (i + 1));
	if (!buff_line)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i] != '\n' && line[i])
		buff_line[j++] = line[i++];
	if (line[i] == '\n')
		buff_line[j++] = line[i++];
	buff_line[j] = '\0';
	return (buff_line);
}

static char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen_gnl(save) - i + 1));
	if (!s)
		return (NULL);
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free(save);
	return (s);
}

static char	*read_line(int fd, char *last_read_line)
{
	char	*buff;
	int		i;
	int		j;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	while (1)
	{
		i = 0;
		j = read(fd, buff, BUFFER_SIZE);
		if (j == -1 || (j == 0 && !last_read_line))
		{
			free (buff);
			return (NULL);
		}
		buff[j] = '\0';
		while (buff[i] != '\n' && buff[i])
			i++;
		last_read_line = ft_strjoin(last_read_line, buff);
		if (i != j || (j == 0 && last_read_line[i] != 0))
			break ;
	}
	free(buff);
	return (last_read_line);
}

char	*gnl(int fd)
{
	static char	*last_read_line;
	char		*new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	last_read_line = read_line(fd, last_read_line);
	new_line = write_new_line(last_read_line);
	last_read_line = ft_save(last_read_line);
	if (last_read_line && last_read_line[0] == '\0')
		free(last_read_line);
	return (new_line);
}
