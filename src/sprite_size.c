/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 15:24:42 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/13 16:11:38 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

void	get_map_dimensions(t_mlx *mlx)
{
	mlx->row_length = ft_row_length(mlx->map->line);
	ft_printf("row length %d\n", mlx->row_length);
	mlx->col_height = get_map_height(mlx->map);
	ft_printf("col height %d\n", mlx->col_height);
}

int	get_sprite_size(t_mlx *mlx)
{
	get_map_dimensions(mlx);
	if (mlx->row_length > 78)
		return (112);
	if (mlx->row_length > 52)
		return (112);
	if (mlx->row_length > 26)
		return (112);
	else 
		return (112);
}