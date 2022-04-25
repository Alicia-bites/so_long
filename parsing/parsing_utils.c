/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 12:06:14 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/17 13:36:36 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../headers/mlx.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../headers/get_next_line.h"


int	ft_panic(int errcode, int i)
{
	// printf("i in ft_panic = %d\n", i);
	ft_putstr_fd("Error", 1, 2);
	if (errcode == WRONG_NARG)
		ft_printf("so_long takes one .ber as arg\n");
	if (errcode == INVALID_ARG)
		ft_printf("Invalid argument col %d.\n", (-i) + 1);
	else if (errcode == INVALID_NARG)
		ft_printf("Number of %c elt is incorrect.\n", (char) i);
	else if (errcode == ISNOT_REC)
		ft_printf("Map is not a rectangle.\n");
	else if (errcode == MALLOC_FAILURE)
		ft_printf("Memory allocation failed.\n");
	else if (errcode == EMPTY_LINE)
		ft_printf("Found an empty line in map file.\n");
	else if (errcode == HOLE_WALL)
		ft_printf("Found a hole in the wall col %d.\n", (-i) + 1);	
	return (errcode);
}

int	check_char(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != '1' && str[i] != '0' && str[i] != 'P' 
			&& str[i] != 'E' && str[i] != '\n' && str[i] != 'C' && str[i] != '\0')
			return (-i);
		i++;
	}
	return (1);
}

int	col_is_wall(char *str)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(str) - 2;
	while (str[i])
	{
		if (i == 0 && str[i] != '1')
			return (-i);
		if (i == max && str[max] != '1' && str[max + 1] != '\n')
			return (-i);
		i++;
	}
	return (1);
}

int	line_is_wall(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != '\n')
			return (-i);
		i++;
	}
	return (1);
}

int	ft_count(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}