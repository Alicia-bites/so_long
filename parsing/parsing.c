/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:39 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/17 13:44:47 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../headers/mlx.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../headers/get_next_line.h"

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

t_list	*ft_read_map(char *argv)
{
	int		fd;
	t_list	*lst;
	char	*line;

	fd = open(argv, O_RDONLY, __O_NOFOLLOW);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		ft_putstr_fd("Error\nWrong or empty file.\n", 1, 2);
		exit(0);
	}
	while (line != NULL)
	{
		lst = ft_create_list(line);
		line = get_next_line(fd);
	}
	ft_print_lst(lst);
	return (lst);
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
		if ((iterator->index == 0 || iterator->index == max) 
			&& line_is_wall(iterator->line) != 1)
				return (ft_panic(HOLE_WALL, line_is_wall(iterator->line)));
		if (col_is_wall(iterator->line) != 1)
			return (ft_panic(HOLE_WALL, col_is_wall(iterator->line)));
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
	if (err >= -7 && err <= -1)
	{
		ft_clear(lst);
		exit(err);
	}
	return (lst);
}
