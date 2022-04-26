/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:04:29 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/26 15:39:01 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

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
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->x, mlx->y);
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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int get_map_height(t_list *map)
{
	t_list	*iterator;
	int	map_height;

	iterator = map;
	while (iterator)
	{
		map_height = iterator->index;
		iterator = iterator->next;		
	}
	return (map_height);
}

int	built_map(t_list *map)
{
	t_list	*iterator;
	t_mlx	mlx;
	t_data	img;
	int	x;
	int	y;
	int	map_length;
	int	map_height;
	int	image_width;
	int	image_height;
	
	mlx.sprite_size = 112;
	map_length = (ft_strlen(map->line) - 1) * mlx.sprite_size;
	map_height = (get_map_height(map)) * mlx.sprite_size;

	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (0);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, map_length, 
		map_height, "Moonkey");
	y = 0;
	iterator = map;
	image_width = 0;
	image_height = 0;
	while (iterator)
	{
		x = 0;
		while (x < map_length)
		{
			if (iterator->line[x / mlx.sprite_size] == 'P')
			{
				mlx.player = mlx_xpm_file_to_image(mlx.mlx_ptr, "./media/moonkey_112x112.xpm", &image_width, &image_height); // peut etre null
				mlx.x = x;
				mlx.y = y;
				mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.image, x, y);
			}
			else if (iterator->line[x / mlx.sprite_size] == '1')
			{
				mlx.image = mlx_xpm_file_to_image(mlx.mlx_ptr, "./media/bleak_desk_pile_of_death_112x112.xpm", &image_width, &image_height); // peut etre null
				mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.image, x, y);

			}
			else if (iterator->line[x / mlx.sprite_size] == 'E')
			{
				mlx.image = mlx_xpm_file_to_image(mlx.mlx_ptr, "./media/exit_112x112.xpm", &image_width, &image_height); // peut etre null
				mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.image, x, y);				
			}
			else if (iterator->line[x / mlx.sprite_size] == 'C')
			{
				mlx.image = mlx_xpm_file_to_image(mlx.mlx_ptr, "./media/form_1_112x112.xpm", &image_width, &image_height); // peut etre null
				mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.image, x, y);
			}
			x += mlx.sprite_size;
		}
		iterator = iterator->next;
		y += mlx.sprite_size;
	}
	mlx_hook(mlx.win_ptr, 17, 0, ft_redcross, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1, ft_key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_image(mlx.mlx_ptr, mlx.image);
	free_mlx(mlx);
	return (0);
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