/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 11:18:56 by yokitaga          #+#    #+#             */
/*   Updated: 2022/12/16 12:28:29 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_get_save(int fd, char *save)
{
	char	*read_result;
	ssize_t	read_size;

	read_result = (char *)malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (read_result == NULL)
		return (ft_free(save));
	read_size = 1;
	while (read_size != 0 && ft_strchr(save, '\n') == NULL)
	{
		read_size = read(fd, read_result, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(read_result);
			return (ft_free(save));
		}
		read_result[read_size] = '\0';
		save = ft_strjoin(save, read_result);
		if (save == NULL)
			break;
	}
	free(read_result);
	return (save);
}

char	*ft_get_outputline(char *save)
{
	size_t	i;
	char	*output_line;

	i = 0;
	if (save[i] == '\0')
		return (NULL);
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	output_line = (char *)malloc(sizeof(char) * (i + 2));
	if (output_line == NULL)
		return (ft_free(save));
	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
	{
		output_line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		output_line[i] = save[i];
		i++;
	}
	output_line[i] = '\0';
	return (output_line);
}

char	*ft_get_next_save(char *save)
{
	size_t	i;
	size_t	j;
	size_t	save_len;
	char	*next_save;

	i = 0;
	while (save[i] != '\0' && save[i] != '\n')
		i++;
	if (save[i] == '\0')
		return (ft_free(save));
	save_len = ft_strlen(save);
	next_save = (char *)malloc(sizeof(char) * (save_len - i + 1));
	if (next_save == NULL)
		return (ft_free(save));
	i++;
	j = 0;
	while (save[i] != '\0')
		next_save[j++] = save[i++];
	next_save[j] = '\0';
	free(save);
	return (next_save);
}

char	*get_next_line(int fd)
{
	static char	*save;
	char		*output_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || INT_MAX < BUFFER_SIZE)
		return (NULL);
	if (save == NULL)
	{
		save = (char *)malloc(sizeof(char) * 1);
		if (save == NULL)
			return (NULL);
		*save = '\0';
	}
	save = ft_read_get_save(fd, save);
	if (save == NULL)
		return (NULL);
	output_line = ft_get_outputline(save);
	save = ft_get_next_save(save);
	return (output_line);
}