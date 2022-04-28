/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:00:37 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/28 18:37:35 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

//put player on the screen
void	ft_render_player(t_mlx *mlx)
{
	render_sprite(mlx, "moonkey", mlx->player_x, mlx->player_y);
}

//clean up screen for player to move around
void	ft_clear_player(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sprites->image,
		mlx->player_x, mlx->player_y);
}

t_list	*get_pos_right_left(t_mlx *mlx)
{
	t_list	*iterator;

	iterator = mlx->map;
	while (iterator->next)
	{	
		if (iterator->index == mlx->player_y / mlx->sprite_size)
			break ;
		iterator = iterator->next;
	}
	return (iterator);
}
