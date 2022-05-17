/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:00:34 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/17 15:10:15 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

int	can_go(t_mlx *mlx, int keycode)
{
	t_list	*y;
	int		count_forms;

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

t_list	*get_y(t_mlx *mlx, int keycode)
{
	t_list	*iterator;

	if (keycode == DOWN)
		iterator = get_y_down(mlx);
	else if (keycode == UP)
		iterator = get_y_up(mlx);
	else if (keycode == RIGHT || keycode == LEFT)
		iterator = get_y_right_left(mlx);
	return (iterator);
}

int	exit_ok(t_mlx *mlx, int keycode, int collectibles)
{
	if (is_exit(mlx, keycode))
	{
		if (collectibles == mlx->n_collectibles)
			return (1);
		else
			return (0);
	}
	return (1);
}

void	move_player(t_mlx *mlx, int keycode, int col)
{
	static int	count = 1;

	if (keycode == UP && can_go(mlx, keycode) && exit_ok(mlx, keycode, col))
	{
		mlx->player_y -= mlx->sprite_size;
		ft_printf("number of moves %d\n\n", count++);
	}
	else if (keycode == DOWN && can_go(mlx, keycode) && exit_ok(mlx, keycode, col))
	{
		mlx->player_y += mlx->sprite_size;
		ft_printf("number of moves %d\n\n", count++);
	}
	else if (keycode == LEFT && can_go(mlx, keycode) && exit_ok(mlx, keycode, col))
	{
		mlx->player_x -= mlx->sprite_size;
		ft_printf("number of moves %d\n\n", count++);
	}
	else if (keycode == RIGHT && can_go(mlx, keycode) && exit_ok(mlx, keycode, col))
	{
		mlx->player_x += mlx->sprite_size;
		ft_printf("number of moves %d\n\n", count++);
	}
}

//define how player move around
int	ft_key_hook(int keycode, t_mlx *mlx)
{
	int			collectibles;
	static int	temp = 0;

	collectibles = is_collectible(mlx, keycode);
	if (keycode != ESC_KEYCODE)
	{	
		if (keycode == UP || keycode == DOWN
			|| keycode == LEFT || keycode == RIGHT)
		{
			ft_clear_player(mlx);
			if (collectibles)
				temp = handle_collec(mlx, collectibles);
			if (is_exit(mlx, keycode))
				found_exit(mlx, temp);
			move_player(mlx, keycode, temp);
			ft_render_player(mlx);
		}
	}
	else
		ft_redcross(mlx, 0);
	return (keycode);
}
