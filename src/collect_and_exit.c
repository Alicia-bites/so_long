/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_and_exit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 14:14:40 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/13 14:23:38 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

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

int	is_exit(t_mlx *mlx, int keycode)
{
	t_list	*y;
	
    y = get_y(mlx, keycode);
    if ((keycode == UP || keycode == DOWN) &&
		y->line[mlx->player_x / mlx->sprite_size] == 'E')
    {
        return (1);
    }
    if (keycode == LEFT && y->line[(mlx->player_x - mlx->sprite_size)
            / mlx->sprite_size] == 'E')
    {
        return (1);                
    }
    if (keycode == RIGHT && y->line[(mlx->player_x + mlx->sprite_size)
            / mlx->sprite_size] == 'E')
    {
        return (1);
    }
	return (0);
}

void	found_exit(t_mlx *mlx, int collectibles)
{
	if (collectibles == mlx->n_collectibles)
		ft_redcross(mlx, 1);
	else
		ft_redcross(mlx, 2);
}

int	handle_collec(t_mlx *mlx, int collectibles)
{
	int temp;

	if (collectibles == mlx->n_collectibles)
		temp = collectibles;
	ft_printf("collected %d form(s)!\nNeed %d more!\n\n", 
		collectibles, mlx->n_collectibles - collectibles);
	return (temp);
}