/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:04:29 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/22 15:07:21 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../headers/mlx.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"

void	ft_clear(t_list *lst)
{
	ft_lstclear(&lst);
	ft_lstclear_back(&lst);
}

void	free_mlx(t_mlx mlx)
{
	printf("Je free %p et %p\n", mlx.mlx_ptr, mlx.win_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr); // alors on a la detruit apres avec arreter la loop
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
}

int	ft_redcross(t_mlx *mlx)
{
	printf("Tu as clique sur la croix rouge\n");
	mlx_loop_end(mlx->mlx_ptr); // Si tu termines pas loop elle continura a afficher la fenetre detruite :/
	return (0);
}

void ft_render_player(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->image, mlx->x, mlx->y);
}

int	ft_key_hook(int keycode, t_mlx *mlx)
{
	if (keycode != ESC_KEYCODE)
	{
		if (keycode == UP)
			mlx->y -= 50;
		else if (keycode == DOWN)
			mlx->y += 50;
		else if (keycode == LEFT)
			mlx->x -= 50;
		else if (keycode == RIGHT)
			mlx->x += 50;
				
		if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
			ft_render_player(mlx);
	}
		
	else
		ft_redcross(mlx);
	return (keycode);
}

int	ft_built_map(t_list *map)
{
	t_list	*iterator;
	t_mlx	mlx;
	int	i;
	int	j;

	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1020, 1020, "Moonkey"); // peut etre null
	mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, i, j, 0xDEADBEEF);
	mlx.y = 0;
	mlx.x = 0;
	i = 0;
	iterator = map;
	while (iterator)
	{
		if (iterator->line[i] == 1)
			
	}
}

int	main(int argc, char **argv)
{
	t_list *map;
	
	map = NULL;
	if (argc != 2)
		return (ft_panic(WRONG_NARG, 0));
	map = ft_parse(argv[1]);
	built_map(map);
	ft_clear(map);
	return (0);
}