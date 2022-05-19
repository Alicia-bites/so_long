/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 09:44:37 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/19 10:12:38 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"
#include "../headers/get_next_line.h"

void	place_wall(t_mlx *mlx, int x, int y)
{
	static int	i = 1;

	if (i == 1)
		render_sprite(mlx, "desk_clock", x, y);
	else if (i == 2)
		render_sprite(mlx, "desk_pile", x, y);
	else if (i == 3)
		render_sprite(mlx, "desk_poison", x, y);
	if (i == 3)
		i = 0;
	i++;
}

void	place_collectibles(t_mlx *mlx, int x, int y)
{
	static int	i = 1;

	if (i == 1)
		render_sprite(mlx, "form_1", x, y);
	else if (i == 2)
		render_sprite(mlx, "form_2", x, y);
	else if (i == 3)
		render_sprite(mlx, "form_3", x, y);
	if (i == 3)
		i = 0;
	i++;
}

//place map elts in winodw
void	place_elt(t_mlx *mlx, int x, int y, int elt)
{
	if (elt == 'P')
	{
		render_sprite(mlx, "moonkey", x, y);
		mlx->player_x = x;
		mlx->player_y = y;
	}
	else if (elt == '1')
		place_wall(mlx, x, y);
	else if (elt == 'E')
		render_sprite(mlx, "exit", x, y);
	else if (elt == 'C')
		place_collectibles(mlx, x, y);
}

//browse map given in argument and initiate drawing
int	draw_map(t_list *map, t_mlx *mlx)
{
	int		x;
	int		y;
	t_list	*iterator;

	y = 0;
	iterator = map;
	mlx->image_width = 0;
	mlx->image_height = 0;
	draw_background(mlx);
	while (iterator)
	{
		x = 0;
		while (x < mlx->map_length)
		{
			place_elt(mlx, x, y, iterator->line[x / mlx->sprite_size]);
			x += mlx->sprite_size;
		}
		iterator = iterator->next;
		y += mlx->sprite_size;
	}
	return (0);
}
