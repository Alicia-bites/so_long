/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:04:29 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/25 16:25:02 by amarchan         ###   ########.fr       */
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

	map_length = (ft_strlen(map->line) - 1) * 64;
	map_height = (get_map_height(map)) * 64;

	mlx.mlx_ptr = mlx_init();
	printf("mlx.mlx_ptr : %p\n", mlx.mlx_ptr);
	if (!mlx.mlx_ptr)
		return (1);
	printf("length = %d\n", map_length);
	printf("height = %d\n", map_height);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, map_length, 
		map_height, "Moonkey"); // peut etre null
	img.img = mlx_new_image(mlx.mlx_ptr, map_length, map_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
		&img.line_length, &img.endian);
	y = 0;
	image_width = 0;
	image_height = 0;
	iterator = map;
	while (iterator)
	{
		x = 0;
		while (x < map_length)
		{
			if (iterator->line[x] == '1')
			{
				mlx.image = mlx_xpm_file_to_image(mlx.mlx_ptr, "./../media/bleak_desk_pile_of_death_64x64.xpm", &image_width, &image_height); // peut etre null
				printf("J'ai charge une image de taille %dx%d\n", image_width, image_height);
				mlx.y = y;
				mlx.x = x;
				x += 64;
			}
			// else if (iterator->line[x] == 'P')
			// {
			// 	my_mlx_pixel_put(&img, x, y, 0x00FF5733);
			// 	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, 
			// 		img.img, x, y);
			// 	x += 64;
			// }
			// else if (iterator->line[x] == 'E')
			// {
			// 	my_mlx_pixel_put(&img, x, y, 0x0036A42D);
			// 	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, 
			// 		img.img, x, y);
			// 	x+= 64;
			// }
			// else if (iterator->line[x] == 'C')
			// {
			// 	my_mlx_pixel_put(&img, x, y, 0x002D66A4);
			// 	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, 
			// 		img.img, x, y);
			// 	x += 64;
			// }
			else
				x += 64;
		}
		printf("x = %d\n", x/64);
		iterator = iterator->next;
		y += 64;
	}
	mlx_hook(mlx.win_ptr, 17, 0, ft_redcross, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1, ft_key_hook, &mlx);
	//	              key ^  ^ pressed (man X11)
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