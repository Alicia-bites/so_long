/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:52:03 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/13 16:01:20 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"

int ft_check_remember(int remember)
{
	if (remember >= BUFFER_SIZE)
		remember = 0;
	else
		remember += 1;
	return (remember);
}

char *ft_get_leftovers(char *buf, int *remember)
{
	int i;
	int len;
	char *line;

	len = *remember;
	while (len < BUFFER_SIZE && buf[len] != '\n')
		len++;
	len -= (*remember);
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (i < (len + 1) && buf[*remember] != '\n')
		line[i++] = buf[(*remember)++];
	if (buf[*remember] == '\n')
		line[i++] = '\n';
	line[i++] = '\0';
	*remember = ft_check_remember(*remember);
	i = 0;
	if (*remember == 0)
		while (i <= BUFFER_SIZE)
			buf[i++] = '\0';
	return (line);
}

char *ft_get_line(char *line, char *buf, int *remember, int has_read)
{
	char *temp;

	buf[has_read] = '\0';
	temp = ft_get_strdup(buf, remember);
	line = ft_realloc_and_concat(line, ft_get_strlen(line),
								 ft_get_strlen(temp), temp);
	return (line);
}

char *ft_check_line(int *remember, char *line)
{
	*remember = BUFFER_SIZE;
	if (ft_get_strlen(line) == 0)
		return (ft_free(line));
	return (line);
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE + 1];
	static int remember;
	char *line;
	int has_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	if (remember > 0)
	{
		line = ft_get_leftovers(buf, &remember);
		if (ft_get_strchr(line, '\n') >= 0)
			return (line);
	}
	while (ft_get_strchr(line, '\n') < 0)
	{
		has_read = read(fd, buf, BUFFER_SIZE);
		if (has_read == -1 || has_read == 0)
			return (ft_check_line(&remember, line));
		line = ft_get_line(line, buf, &remember, has_read);
	}
	return (line);
}
