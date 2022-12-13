/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yokitaga <yokitaga@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:54:59 by yokitaga          #+#    #+#             */
/*   Updated: 2022/12/13 13:45:19 by yokitaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_get_save(int fd, char *save)
{
	char	*read_result;
	ssize_t	read_size;

	read_result = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_result == NULL)
		return (NULL);
	read_size = 1;
	while (read_size != 0 && ft_strchr(save, '\n') == NULL)//読み終わるか改行見つけるまでwhile回す
	{
		read_size = read(fd, read_result, BUFFER_SIZE);
		if (read_size == -1)//読み込み失敗した場合は読み込み結果とそれまでのsaveをfreeする必要(初回のsaveもmallocで1確保してヌル終端入れているのでfreeしないといけない)
		{
			free(read_result);
			free(save);
			return (NULL);
		}
		read_result[read_size] = '\0';
		save = ft_strjoin(save, read_result);//読み込み結果とsaveをjoinしていく
		if (save == NULL)
			return(NULL);
	}
	free(read_result);//while文抜けるとread_result必要無くなるのでfree
	return (save);//saveには全部読み終わったものが入っているか改行含んだものが入っているか
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
	output_line = (char *)malloc(sizeof(char) * (i + 2));//改行ある時は改行+終端なので確保
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
	if (save[i] == '\0')//next_saveはもうないため、freeして終了。outputlineに既に入っているのでsavewをfreeして良い。
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
	static char	*save;
	char		*output_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (save == NULL)//初期
	{
		save = (char *)malloc(sizeof(char) * 1);
		if (save == NULL)
			return (NULL);
		*save = '\0';
	}
	save = ft_read_get_save(fd, save);
	if (save == NULL)
		return (NULL);
	output_line = ft_get_outputline(save);//saveには全部読み終わったものが入っているか、改行含んだものが入っているいる→そこからouputline取り出す
	save = ft_get_next_save(save);
	return (output_line);
}