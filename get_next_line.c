/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-b <uviana-b@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:23:48 by uviana-b          #+#    #+#             */
/*   Updated: 2024/11/22 06:55:01 by uviana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*save_stock(char *stock)
{
	char	*ret;
	char	*newline;

	if (!stock || !(newline = ft_strchr(stock, '\n')))
		return (NULL);
	ret = ft_substr(stock, (newline - stock) + 1, ft_strlen(stock));
	free(stock);
	return (ret);
}

char	*save_line(char *stock)
{
	char	*line;
	char	*newline;

	if (!stock)
		return (NULL);
	newline = ft_strchr(stock, '\n');
	if (!newline)
		return (ft_strdup(stock));
	line = ft_substr(stock, 0, newline - stock + 1);
	return (line);
}

char	*my_reader(char *stock, int fd)
{
	char	*reader;
	int		bytes_read;

	bytes_read = 0;
	reader = (char *)malloc(BUFFER_SIZE + 1);
	if (!reader)
		return (NULL);
	while (!ft_strchr(stock, '\n') && (bytes_read = read(fd, reader, BUFFER_SIZE)) > 0)
	{
		reader[bytes_read] = '\0';
		stock = ft_strjoin(stock, reader);
	}
	free(reader);
	if (bytes_read < 0) // Erro de leitura
	{
		free(stock);
		return (NULL);
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = my_reader(stock, fd);
	if (!stock)
		return (NULL);
	line = save_line(stock);
	stock = save_stock(stock);
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd = open("text.txt", O_RDONLY);
	char *line;

	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
