/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:24:42 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/18 11:54:09 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

void	get_map_dimensions(t_mlx *mlx)
{
	mlx->row_length = ft_row_length(mlx->map->line);
	mlx->col_height = get_map_height(mlx->map);
}

int	get_sprite_size(t_mlx *mlx)
{
	get_map_dimensions(mlx);
	if (mlx->row_length > 81 || mlx->col_height > 43)
	{
		ft_printf("You map is too big!\n" \
			"Usage : row length < 81, column height < 43\n" \
			"Max map size : 80x42.\n");
		exit(0);
	}
	if (mlx->row_length > 53 || mlx->col_height > 28)
		return (32);
	if (mlx->row_length > 41 || mlx->col_height > 22)
		return (48);
	if (mlx->row_length > 33 || mlx->col_height > 18)
		return (64);
	if (mlx->row_length > 23 || mlx->col_height > 13)
		return (80);
	else
		return (112);
}
