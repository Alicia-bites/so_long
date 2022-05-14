/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:46:11 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/14 17:03:37 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *s1, const void *s2, int n)
{
	char		*dest;
	const char	*src;
	int			i;

	i = 0;
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	dest = (char *)s1;
	src = (const char *)s2;
	while (i < (n))
	{
		dest[i] = src[i];
		i++;
	}
	return (s1);
}
