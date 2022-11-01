/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 00:19:23 by yokitaga          #+#    #+#             */
/*   Updated: 2022/11/01 13:15:31 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_read_get_save(int fd, char *save)
{
	char	*read_result;
	ssize_t	read_size;

	read_result = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_result == NULL)
		return (NULL);
	read_size = 1;
	while (read_size != 0 && ft_strchr(save, '\n') == NULL)
	{
		read_size = read(fd, read_result, BUFFER_SIZE);
		if (read_size == -1)
		{
			free(read_result);
			free(save);
			return (NULL);
		}
		read_result[read_size] = '\0';
		save = ft_strjoin(save, read_result);
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
		return (NULL);
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
	{
		free(save);
		return (NULL);
	}
	save_len = ft_strlen(save);
	next_save = (char *)malloc(sizeof(char) * (save_len - i + 1));
	if (next_save == NULL)
		return (NULL);
	i++;//改行の次からコピーしたいため
	j = 0;
	while (save[i] != '\0')
		next_save[j++] = save[i++];
	next_save[j] = '\0';
	free(save);
	return (next_save);
}

char	*get_next_line(int fd)
{
	static char	*save[MAX_FD];
	char		*output_line;

	if (fd < 0 || MAX_FD < fd || BUFFER_SIZE <= 0)
		return (NULL);
	if (save[fd] == NULL)
	{
		save[fd] = (char *)malloc(sizeof(char) * 1);
		*save[fd] = '\0';
	}
	save[fd] = ft_read_get_save(fd, save[fd]);
	if (save[fd] == NULL)
		return (NULL);
	output_line = ft_get_outputline(save[fd]);
	save[fd] = ft_get_next_save(save[fd]);
	return (output_line);
}
