/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:53:03 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/18 12:03:14 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **first_elt, t_list *new)
{
	t_list	*iterator;

	iterator = *first_elt;
	if (first_elt && new)
	{
		if (!*first_elt)
			*first_elt = new;
		else
		{	
			while (iterator->next)
				iterator = iterator->next;
			iterator->next = new;
			new->prev = iterator;
		}
	}
}
