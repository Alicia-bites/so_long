/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:58:10 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/28 18:33:21 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

//compute map height
int	get_map_height(t_list *map)
{
	t_list	*iterator;
	int		map_height;

	iterator = map;
	while (iterator)
	{
		map_height = iterator->index;
		iterator = iterator->next;
	}
	return (map_height + 1);
}

//open background image and display in window
void	draw_background(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < mlx->map_length)
	{
		y = 0;
		while (y < mlx->map_height)
		{
			render_sprite(mlx, "bg", x, y);
			y += mlx->sprite_size;
		}
		x += mlx->sprite_size;
	}
}
