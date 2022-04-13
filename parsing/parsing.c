/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:39 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/13 18:11:41 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../headers/mlx.h"
#include "../libft/libft.h"
#include "../headers/get_next_line.h"

int	ft_panic(int errcode)
{
	if (errcode == WRONG_NARG)
		ft_putstr_fd("Error", 1, 2);
	else if (errcode == INVALID_ARG)
		ft_putstr_fd("Error", 1, 2);
	else if (errcode == MALLOC_FAILURE)
		ft_putstr_fd("Error", 1, 2);
	return (errcode);
}

t_list	*ft_create_list(char *line)
{
	static int		i = 0;
	static t_list	*lst;
	t_list			*new;

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
}

t_list	*ft_parse(char *argv)
{	
	int		fd;
	t_list	*lst;
	char	*line;
	
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lst = ft_create_list(line);
		// free(line); a free quand ca ferme
		line = get_next_line(fd);
	}
	ft_print_lst(lst);
	return (lst);
}
