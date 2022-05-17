/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 12:12:52 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/17 15:58:21 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../headers/mlx.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"
#include "../headers/get_next_line.h"

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
	int		len;
	int		index;
	t_list	*iterator;

	iterator = lst;
	len = 0;
	index = 0;
	while (iterator)
	{
		if (iterator->index == 0)
			len = ft_row_length(iterator->line);
		if (ft_row_length(iterator->line) != len)
			ft_panic(ISNOT_REC, 0, &lst);
		iterator = iterator->next;
	}
}

int	ft_count_elts(t_list *lst)
{
	t_list	*iterator;
	int		count_p;
	int		count_e;
	int		count_c;

	iterator = lst;
	count_p = 0;
	count_e = 0;
	count_c = 0;
	while (iterator)
	{
		count_p += ft_count(iterator->line, 'P');
		count_e += ft_count(iterator->line, 'E');
		count_c += ft_count(iterator->line, 'C');
		iterator = iterator->next;
	}
	if (count_p != 1)
		ft_panic(INVALID_NARG, 'P', &lst);
	if (count_e != 1)
		ft_panic(INVALID_NARG, 'E', &lst);
	if (count_c < 1)
		ft_panic(INVALID_NARG, 'C', &lst);
	return (1);
}

int	wrong_file(char *str)
{
	int	l;

	l = ft_strlen(str) - 1;
	if (str[l] != 'r' ||  str[l - 1] != 'e'
		|| str[l - 2] != 'b' || str[l - 3] != '.')
		return (1);
	return (0);
}
