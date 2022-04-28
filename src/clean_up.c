/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:11:33 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/28 17:45:09 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

void	destroy_sprites(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (mlx->sprites[i].image)
	{
		printf("i = %d\n", i);
		fflush(0);
		mlx_destroy_image(mlx->mlx_ptr, mlx->sprites[i++].image);
	}
}

void	ft_clear(t_list *lst)
{
	ft_lstclear(&lst);
	ft_lstclear_back(&lst);
}

void	free_mlx(t_mlx *mlx)
{
	printf("I free  mlx.mlx_ptr (%p) and mlx.win_ptr (%p)\n", mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	free(mlx->sprites);
}
