/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:58:55 by amarchan          #+#    #+#             */
/*   Updated: 2022/09/01 13:45:30 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"


//close window
int	ft_redcross(t_mlx *mlx, int x)
{
	if (x == 0)
		ft_printf("Leaving the game. See you later!\n");
	if (x == 1)
		ft_printf(
			"WINNER! You collected all the forms and you are " \
			"free from bureaucracie! Until the next time...\n");
	if (x == 2)
		ft_printf(
			"LOOSER! You didn't collect all the forms! " \
			"Your soul belong to us now...\n");
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

//put pixels in windows
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
