/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:39 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/14 14:01:21 by amarchan         ###   ########.fr       */
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
	if (errcode == WRONG_NARG)
		ft_putstr_fd("Error", 1, 2);
	else if (errcode == INVALID_ARG)
	{
		ft_putstr_fd("Error", 1, 2);
		ft_printf("Invalid argument col %d\n", i);
	}
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

t_list	*ft_parse(char *argv)
{	
	int		fd;
	int		err;
	t_list	*lst;
	char	*line;
	
	fd = open(argv, O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		lst = ft_create_list(line);
		//  free(line); a free quand ca ferme
		line = get_next_line(fd);
	}
	ft_print_lst(lst);
	err = ft_check_elts(lst);
	if (err > -3 && err < -1)
	{
		ft_clear(lst);
		exit(err);
	}
	return (lst);
}
