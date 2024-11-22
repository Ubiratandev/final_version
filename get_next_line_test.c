/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uviana-b <uviana-b@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:23:48 by uviana-b          #+#    #+#             */
/*   Updated: 2024/11/22 06:19:55 by uviana-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = (char *) malloc((ft_strlen((char *)s1)
				+ ft_strlen((char *)s2)) * sizeof (char) + 1);
	if (ret == 0)
		return (0);
	while (s1[i])
	{
		ret[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		ret[j] = s2[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	free (s1);
	return (ret);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*str;
	unsigned char	chr;

	str = (unsigned char *)s;
	chr = (unsigned char)c;
	if (s == NULL)
		return (NULL);
	while (*str != chr && *str != 0)
		str++;
	if (*str == chr)
		return ((char *)str);
	return (0);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*str;

	if (!s)
		return (0);
	size = ft_strlen(s);
	if (start > size)
	{
		start = size;
		size = 0;
	}
	else
		size -= start;
	if (size > len)
		size = len;
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (s[start] != 0 && i < size)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

char	*save_stock(char *stock)
{
	char	*ret;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (stock[i] != '\n')
	{
		i++;
	}
	if (stock[i + 1] == '\0')
		return (NULL);
	while(stock[i + j])
	{
		j++;
	}
	if (stock)
	{
		ret = ft_substr(stock, i, j);
		free(stock);
	}
	else
	{
		ret = (char *) malloc(sizeof(char) * 1);
		*ret = '\0';
	}

	return (ret);
}
char	*save_line(char *stock)
{
	char	*ret;
	int	i;

	i = 0; 
 	while (stock[i] && stock[i] != '\n')
		i++;
	/*if (stock[i + 1] == '\0')
		return (NULL);*/
	ret = (char *) malloc(sizeof(char) * i + 1);
	i = 0;
	while(stock[i] && stock[i] != '\n')
	{
		ret[i] =  stock[i];
		i++;
	}
	if (stock[i] == '\n')
		ret[i] = '\n';
	return (ret);
	
}

char	*my_reader(char	*stock, int fd)
{
	char	*reader;
	int	count_read;

	count_read = 1;
	reader = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!stock)
	{
	       	stock = (char *) malloc(1);
		*stock = '\0';;
	}
	count_read =  read(fd, reader,BUFFER_SIZE);
	while (count_read > 0)
	{
		if(!ft_strchr(reader, '\n'))
		{

			 count_read = read(fd, reader, BUFFER_SIZE);
			 if (count_read < 0)
			 {
				free(reader);
				return (stock);
			 }
			 reader[ft_strlen(reader) + 1] = '\0';
			  stock = ft_strjoin(stock, reader);
		}
		else
		{
			stock = ft_strjoin(stock, reader);
			count_read = 0;
		}
	}
	return (stock);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char	*print;
	int	count_read;

	count_read = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	stock =  my_reader(stock, fd);
	print = save_line(stock);
	stock = save_stock(stock);
	return (print);

}
#include<stdio.h>
int     main (void)
{
        int     fd;

        fd = open ("text.txt", O_RDONLY);
	char *str = get_next_line(fd);
	printf("%s ", str);
	while (str != 0)
	{
		str = get_next_line(fd);
		printf("%s ", str);
		free(str);
	}
	free(str);
//	printf("%s", get_next_line(fd));
//	printf("%s", get_next_line(fd));
        return (0);
}
