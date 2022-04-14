/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:39 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/14 18:14:56 by amarchan         ###   ########.fr       */
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
		ft_printf("so_long takes one .ber as arg");
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
		ft_printf("Found a hole in the wall col %d.\n", i);	
	return (errcode);
}

t_list	*ft_create_list(char *line)
{
	static int		i = 0;
	static t_list	*lst;
	t_list			*new;

	if (ft_strlen(line) < 2)
	{
		ft_clear(lst);
		exit (ft_panic(EMPTY_LINE, 0));
	}
	if (i == 0)
		lst = ft_lstnew(line, i);
	else
	{
		new = ft_lstnew(line, i);
		ft_lstadd_back(&lst, new);
	}	
	i++;
	return (lst);
}

void	ft_print_lst(t_list *lst)
{
	t_list *iterator;

	iterator = lst;
	while (iterator)
	{
		printf("index = %d\n", iterator->index);
		printf("%s", iterator->line);
		iterator = iterator->next;		
	}
	puts("\n");
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

//returns error INVALID ARG if a char different from
//1, 0, P, E, C, and \n is found
int	ft_check_elts(t_list *lst)
{
	t_list	*iterator;
	
	iterator = lst;
	while (iterator)
	{
		if ((check_char(iterator->line) != 1))
			return (ft_panic(INVALID_ARG, check_char(iterator->line)));		
		iterator = iterator->next;
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

int	ft_count_elts(t_list *lst)
{
	t_list	*iterator;
	int	count_p;
	int	count_c;
	int	count_e;

	iterator = lst;
	count_p = 0;
	count_c = 0;
	count_e = 0;
	while (iterator)
	{
		count_p += ft_count(iterator->line, 'P');
		count_c += ft_count(iterator->line, 'C');
		count_e += ft_count(iterator->line, 'E');
		iterator = iterator->next;
	}
	if (count_p != 1)
		return (ft_panic(INVALID_NARG, 'P'));
	if (count_c != 1)
		return (ft_panic(INVALID_NARG, 'C'));
	if (count_e != 1)
		return (ft_panic(INVALID_NARG, 'E'));
	return (1);
}

t_list	*ft_read_map(char *argv)
{
	int		fd;
	t_list	*lst;
	char	*line;

	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lst = ft_create_list(line);
		line = get_next_line(fd);
	}
	ft_print_lst(lst);
	return (lst);
}

int	ft_row_length(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	is_rectangular(t_list *lst)
{
	int	len;
	int	index;
	t_list	*iterator;

	iterator = lst;
	len = 0;
	index = 0;
	while (iterator)
	{
		if (iterator->index == 0)
			len = ft_row_length(iterator->line);
		if (ft_row_length(iterator->line) != len)
			return (ft_panic(ISNOT_REC, 0));
		iterator = iterator->next;
	}
}

int	col_is_not_a_wall(char *str)
{
	int	i;
	int	max;

	i = 0;
	max = ft_strlen(str);
	printf("max = %d\n", max);
	while (str[i])
	{
		if (i == 0 && str[i] != 1)
			return (-i);
		if (i == max && str[i] != 1)
			return (-1);
		i++;
	}
	return (0);
}

int	line_is_not_a_wall(char *str)
{
	int	i;

	while (str[i])
	{
		if (str[i] != 1)
			return (-i);
		i++;
	}
	return (0);
}

int	ft_check_walls(t_list *lst)
{
	t_list *iterator;
	int	max;

	iterator = lst;
	while (iterator->next)
		iterator = iterator->next;
	max = iterator->index;
	iterator = lst;
	while (iterator)
	{
		if (iterator->index == 0 || iterator->index == max 
			|| line_is_not_a_wall(iterator->line) != 0)
			return (ft_panic(HOLE_WALL, line_is_not_a_wall(iterator->line)));
		if (col_is_not_a_wall(iterator->line) != 0)
			return (ft_panic(HOLE_WALL, col_is_not_a_wall(iterator->line)));
		iterator = iterator->next;
	}
	return (1);
}

t_list	*ft_parse(char *argv)
{	
	
	int		err;
	t_list	*lst;
	
	lst = ft_read_map(argv);
	err = is_rectangular(lst);
	err = ft_check_elts(lst);
	err = ft_count_elts(lst);
	err = ft_check_walls(lst);
	if (err > -5 && err < -1)
	{
		ft_clear(lst);
		exit(err);
	}
	return (lst);
}
