/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 18:00:34 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/11 18:10:01 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

t_list	*get_pos_down(t_mlx *mlx)
{
	t_list	*iterator;

	iterator = mlx->map;
	while (iterator)
	{	
		if (iterator->index == (mlx->player_y + mlx->sprite_size)
			/ mlx->sprite_size)
			break ;
		iterator = iterator->next;
	}
	return (iterator);
}

t_list	*get_pos_up(t_mlx *mlx)
{
	t_list	*iterator;

	iterator = mlx->map;
	while (iterator)
	{	
		if (iterator->index == (mlx->player_y - mlx->sprite_size)
			/ mlx->sprite_size)
			break ;
		iterator = iterator->next;
	}
	return (iterator);
}

t_list	*get_y(t_mlx *mlx, int keycode)
{
	t_list	*iterator;

	if (keycode == DOWN)
		iterator = get_pos_down(mlx);
	else if (keycode == UP)
		iterator = get_pos_up(mlx);
	else if (keycode == RIGHT || keycode == LEFT)
		iterator = get_pos_right_left(mlx);
	return (iterator);
}

t_list	*get_pos_for_E_C(t_mlx *mlx)
{
	t_list	*iterator;

	iterator = mlx->map;
	while (iterator)
	{	
		if (iterator->index == mlx->player_y
			/ mlx->sprite_size)
			break ;
		iterator = iterator->next;
	}
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

int	is_collectible(t_mlx *mlx, int keycode)
{
	t_list	*y;
	int	count_forms;
	int	been_there;
	
	count_forms = 1;
	been_there = ft_been_there(mlx);
	y = get_y(mlx, keycode);
	if (keycode == UP && y->line[(mlx->player_x) / mlx->sprite_size] == 'C' && 
		been_there)
		return (count_forms++);
	if (keycode == DOWN && y->line[(mlx->player_x) / mlx->sprite_size] == 'C')
		return (count_forms++);
	if (keycode == LEFT && y->line[(mlx->player_x - mlx->sprite_size)
			/ mlx->sprite_size] == 'C')
		return (count_forms++);
	if (keycode == RIGHT && y->line[(mlx->player_x + mlx->sprite_size)
			/ mlx->sprite_size] == 'C')
		return (count_forms++);
	return (0);
}

//define how player move around
int	ft_key_hook(int keycode, t_mlx *mlx)
{
	if (keycode != ESC_KEYCODE)
	{				
		if (keycode == UP || keycode == DOWN || keycode == LEFT
			|| keycode == RIGHT)
		{
			ft_clear_player(mlx);
			if (is_collectible(mlx, keycode))
				ft_printf("collected %d form\n", is_collectible(mlx, keycode));
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



