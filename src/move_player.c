/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:00:34 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/13 14:17:17 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

int	can_go(t_mlx *mlx, int keycode)
{
	t_list	*y;
	int	count_forms;
	
	y = get_y(mlx, keycode);
	if (keycode == UP && y->line[(mlx->player_x) / mlx->sprite_size] == '1')
		return (0);
	if (keycode == DOWN && y->line[(mlx->player_x) / mlx->sprite_size] == '1')
		return (0);
	if (keycode == LEFT && y->line[(mlx->player_x - mlx->sprite_size)
			/ mlx->sprite_size] == '1')
		return (0);
	if (keycode == RIGHT && y->line[(mlx->player_x + mlx->sprite_size)
			/ mlx->sprite_size] == '1')
		return (0);
	return (1);
}

//define how player move around
int	ft_key_hook(int keycode, t_mlx *mlx)
{
	int	collectibles;
	static int	temp = 0;

	collectibles = is_collectible(mlx, keycode);
	if (keycode != ESC_KEYCODE)
	{				
		ft_clear_player(mlx);
		if (collectibles)
			temp = handle_collec(mlx, collectibles);
		if (is_exit(mlx, keycode))
			found_exit(mlx, temp);
		if (keycode == UP && can_go(mlx, keycode))
			mlx->player_y -= mlx->sprite_size;
		else if (keycode == DOWN && can_go(mlx, keycode))
			mlx->player_y += mlx->sprite_size;
		else if (keycode == LEFT && can_go(mlx, keycode))
			mlx->player_x -= mlx->sprite_size;
		else if (keycode == RIGHT && can_go(mlx, keycode))
			mlx->player_x += mlx->sprite_size;
		ft_render_player(mlx);
	}
	else
		ft_redcross(mlx, 0);
	return (keycode);
}



