/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:51:46 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/13 16:02:08 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"

int	ft_get_strlen(char *str)
{
	int	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_get_strdup(char *src, int *remember)
{
	int		i;
	int		len;
	char	*copy;

	len = 0;
	if (!src)
		return (NULL);
	while (len < BUFFER_SIZE && src[len - 1] != '\n')
		len++;
	copy = malloc(sizeof(char) * (len + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < len && src[i - 1] != '\n')
	{
		copy[i] = src[i];
		i++;
	}
	copy[i] = '\0';
	if (remember != NULL)
		*remember = len;
	return (copy);
}

int	ft_get_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != c)
	{
		if (s[i] == '\0')
			return (-1);
		i++;
	}
	return (i);
}

char	*ft_realloc_and_concat(char *str, size_t oldsize,
				size_t newsize, char *newstr)
{
	size_t	destsize;
	char	*dest;
	size_t	i;
	size_t	j;

	if (!newstr)
		return (NULL);
	destsize = newsize + oldsize;
	dest = malloc(sizeof(char) * destsize + 1);
	if (!dest)
	{
		ft_free(str);
		return (ft_free(newstr));
	}
	i = -1;
	while (++i < oldsize)
		dest[i] = str[i];
	j = 0;
	while (j < newsize)
		dest[i++] = newstr[j++];
	dest[destsize] = '\0';
	free(newstr);
	free(str);
	return (dest);
}

char	*ft_free(char *str)
{
	if (str)
		free(str);
	return (NULL);
}

// int main()
// {
// 	char *str = "alicia";
//  	char *newstr = "PA";
//  	size_t newsize = 2;
//  	size_t oldsize = 6;

// 	printf("%s\n", ft_realloc_and_concat(str, oldsize, newsize, newstr));
// 	return (0);
// }