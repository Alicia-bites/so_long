/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_back.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:30:19 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/18 12:02:43 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//clear the list starting from the LAST element
void	ft_lstclear_back(t_list **lst)
{
	t_list	*iterator;
	t_list	*prev;

	if (*lst == NULL)
		return ;
	iterator = *lst;
	prev = NULL;
	while (iterator->prev)
	{
		prev = iterator;
		iterator = iterator->prev;
		free(prev);
	}
	free(iterator);
	*lst = NULL;
}
