/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:39 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/19 11:02:42 by amarchan         ###   ########.fr       */
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
		free(line);
		ft_panic(EMPTY_LINE, 0, &lst);
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

//FOR DEBUG
// void	ft_print_lst(t_list *lst)
// {
// 	t_list *iterator;

// 	iterator = lst;
// 	while (iterator)
// 	{
// 		ft_printf("index = %d\n", iterator->index);
// 		ft_printf("%s", iterator->line);
// 		iterator = iterator->next;		
// 	}
// 	puts("\n");
// }

//returns error INVALID ARG if a char different from
//1, 0, P, E, C, and \n is found
int	ft_check_elts(t_list *lst)
{
	t_list	*iterator;

	iterator = lst;
	while (iterator)
	{
		if ((check_char(iterator->line) != 1))
			ft_panic(INVALID_ARG, check_char(iterator->line), &lst);
		iterator = iterator->next;
	}
	return (1);
}

t_list	*ft_read_map(char *argv)
{
	int		fd;
	t_list	*lst;
	char	*line;

	if (wrong_file(argv))
	{
		ft_putstr_fd("Error\nWrong type of file or empty file.\n", 1, 2);
		exit (FILE_ERROR);
	}
	fd = open(argv, O_RDONLY, __O_NOFOLLOW);
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		ft_putstr_fd("Error\nWrong type of file or empty file.\n", 1, 2);
		exit(FILE_ERROR);
	}
	while (line != NULL)
	{
		lst = ft_create_list(line);
		line = get_next_line(fd);
	}
	return (lst);
}

int	ft_check_walls(t_list *lst)
{
	t_list	*iterator;
	int		max;

	iterator = lst;
	while (iterator->next)
		iterator = iterator->next;
	max = iterator->index;
	iterator = lst;
	while (iterator)
	{
		if ((iterator->index == 0 || iterator->index == max)
			&& line_is_wall(iterator->line) != 1)
			ft_panic(HOLE_WALL, line_is_wall(iterator->line), &lst);
		if (col_is_wall(iterator->line) != 1)
			ft_panic(HOLE_WALL, col_is_wall(iterator->line), &lst);
		iterator = iterator->next;
	}
	return (1);
}

t_list	*ft_parse(char *argv)
{	
	t_list	*lst;

	lst = ft_read_map(argv);
	is_rectangular(lst);
	ft_check_elts(lst);
	ft_count_elts(lst);
	ft_check_walls(lst);
	return (lst);
}
