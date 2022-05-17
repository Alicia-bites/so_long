/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 12:11:33 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/17 16:05:45 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

void	ft_clear_file_loc(char **tab)
{
	int	i;

	i = 0;
	while (i <= 8)
		free(tab[i++]);
}

void	destroy_sprites(t_mlx *mlx)
{
	int	i;

	if (mlx)
	{
		i = 0;
		while (i <= 8)
			mlx_destroy_image(mlx->mlx_ptr, mlx->sprites[i++].image);
	}
}

void	ft_clear(t_list **lst)
{
	if (*lst)
	{
		ft_lstclear(lst);
		ft_lstclear_back(lst);
	}
}

void	free_mlx(t_mlx *mlx)
{
	if (mlx->map)
		ft_clear(&(mlx->map));
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_destroy_display(mlx->mlx_ptr);
	free(mlx->mlx_ptr);
	if (mlx->sprites)
		free(mlx->sprites);
}
