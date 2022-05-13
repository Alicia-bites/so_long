/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:00:34 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/13 11:34:07 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

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

// int	been_up_down(t_mlx *mlx, int keycode)
// {
// 	static int	was_y = -1;
// 	static int	was_x = -1;
	
// 	if (keycode == UP && was_x == mlx->player_x)
// 	{
// 		if (was_y == mlx->player_y - mlx->sprite_size)
// 			return (1);
// 		else
// 			{
// 				was_x = mlx->player_x;
// 				was_y = mlx->player_y;
// 				return (0);
// 			}		
// 	}
// 	if (keycode == DOWN && was_x == mlx->player_x)
// 	{
// 		if (was_y == mlx->player_y + mlx->sprite_size)
// 			return (1);
// 		else
// 			{
// 				was_x = mlx->player_x;
// 				was_y = mlx->player_y;
// 				return (0);
// 			}		
// 	}
// }

// int	been_right_left(t_mlx *mlx, int keycode)
// {
// 	static int	was_y = -1;
// 	static int	was_x = -1;
	
// 	if (keycode == RIGHT && was_y == mlx->player_y)
// 	{
// 		if (was_y == mlx->player_x - mlx->sprite_size)
// 			return (1);
// 		else
// 			{
// 				was_x = mlx->player_x;
// 				was_y = mlx->player_y;
// 				return (0);
// 			}		
// 	}
// 	if (keycode == LEFT && was_y == mlx->player_y)
// 	{
// 		if (was_y == mlx->player_x + mlx->sprite_size)
// 			return (1);
// 		else
// 			{
// 				was_x = mlx->player_x;
// 				was_y = mlx->player_y;
// 				return (0);
// 			}		
// 	}
// 	return (1);
// }

// int	been_there(t_mlx *mlx, int keycode)
// {
// 	static int	first = 1;

// 	if (first)
// 	{
// 		first = 0;
// 		return (0);
// 	}
// 	else
// 	{
// 		if ((keycode == UP || keycode == DOWN) && been_up_down(mlx, keycode))
// 			return (1);
// 		else if ((keycode == RIGHT || keycode == LEFT) && 
// 			been_right_left(mlx, keycode))
// 			return (1);
// 		return (0);
// 	}
// }

int	is_collectible(t_mlx *mlx, int keycode)
{
	t_list	*y;
	static int	count_forms = 1;
	
    y = get_y(mlx, keycode);
    if ((keycode == UP || keycode == DOWN) &&
		y->line[mlx->player_x / mlx->sprite_size] == 'C')
    {
        y->line[mlx->player_x / mlx->sprite_size] = '0';
        return (count_forms++);
    }
    if (keycode == LEFT && y->line[(mlx->player_x - mlx->sprite_size)
            / mlx->sprite_size] == 'C')
    {
        y->line[(mlx->player_x - mlx->sprite_size) / mlx->sprite_size] = '0';
        return (count_forms++);                
    }
    if (keycode == RIGHT && y->line[(mlx->player_x + mlx->sprite_size)
            / mlx->sprite_size] == 'C')
    {
        y->line[(mlx->player_x + mlx->sprite_size) / mlx->sprite_size] = '0';
        return (count_forms++);
    }
	return (0);
}

//define how player move around
int	ft_key_hook(int keycode, t_mlx *mlx)
{
	int	collectible;

	collectible = is_collectible(mlx, keycode);
	if (keycode != ESC_KEYCODE)
	{				
		if (keycode == UP || keycode == DOWN || keycode == LEFT
			|| keycode == RIGHT)
		{
			ft_clear_player(mlx);
			if (collectible)
				ft_printf("collected %d form(s)\n", collectible);
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
	}
	else
		ft_redcross(mlx, 0);
	return (keycode);
}



