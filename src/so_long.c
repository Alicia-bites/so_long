/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:04:29 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/27 19:00:46 by amarchan         ###   ########.fr       */
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
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, mlx->x, mlx->y);
}

void ft_clear_player(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->background, mlx->x, mlx->y);
}

int	ft_key_hook(int keycode, t_mlx *mlx)
{
	if (keycode != ESC_KEYCODE)
	{				
		if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT)
		{
			ft_clear_player(mlx);
			if (keycode == UP)
				mlx->y -= mlx->sprite_size;
			else if (keycode == DOWN)
				mlx->y += mlx->sprite_size;
			else if (keycode == LEFT)
				mlx->x -= mlx->sprite_size;
			else if (keycode == RIGHT)
				mlx->x += mlx->sprite_size;
			ft_render_player(mlx);
		}
		
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

void	draw_background(t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < mlx->map_length)
	{
		y = 0;
		while (y < mlx->map_height)
		{
			mlx->background = mlx_xpm_file_to_image(mlx->mlx_ptr, "./media/background_1_112x112.xpm", &mlx->image_width, &mlx->image_height); // peut etre null
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->background, x, y);
			y += mlx->sprite_size;
		}
		x += mlx->sprite_size;
	}
}

void	move_player(t_list *map, t_mlx *mlx, int x, int y)
{
	mlx->player = mlx_xpm_file_to_image(mlx->mlx_ptr, "./media/moonkey_112x112.xpm", &mlx->image_width, &mlx->image_height);
	mlx->x = x;
	mlx->y = y;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->player, x, y);
}

t_sprite	load_sprite(t_mlx *mlx, char *path, char *name)
{
	t_sprite output;

	output.image = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &mlx->image_width, &mlx->image_height);
	output.name = name;
	if (!output.image)
		exit(EXIT_FAILURE); // TODO : Quitter et liberer la mlx et les sprites
	return (output);
}

void	load_images(t_mlx *mlx)
{
	// t_sprite	tab[SPRITE_COUNT];
	t_sprite	*arr;

	arr = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	ft_bzero(arr, sizeof(t_sprite) * SPRITE_COUNT);
	
	arr[0] = load_sprite(mlx, "./media/background_1_112x112.xpm", "bg");
	arr[1] = load_sprite(mlx, "./media/bleak_desk_clock_112x112.xpm", "desk_clock");
	arr[2] = load_sprite(mlx, "./media/bleak_desk_pile_of_death_112x112.xpm", "desk_pile");
	arr[3] = load_sprite(mlx, "./media/bleak_desk_poison_water_112x112.xpm", "desk_poison");
	arr[4] = load_sprite(mlx, "./media/exit_112x112.xpm", "exit");
	arr[5] = load_sprite(mlx, "./media/form_1_112x112.xpm", "form_1");
	arr[6] = load_sprite(mlx, "./media/form_2_112x112.xpm", "form_2");
	arr[7] = load_sprite(mlx, "./media/form_3_112x112.xpm", "form_3");
	arr[8] = load_sprite(mlx, "./media/moonkey_112x112.xpm", "moonkey");	
	mlx->sprites = arr;
}

void	render_sprite(t_mlx *mlx, char *name, int x, int y)
{
	int	i;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (ft_strcmp(name, mlx->sprites[i].name) == 0)
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sprites[i].image, x, y);
			return ;
		}
		i++;
	}
}

void	place_elt(t_list *map, t_mlx *mlx, int x, int y, int elt)
{
	if (elt == 'P')
		move_player(map, mlx, x, y);
	else if (elt == '1')
	{
		render_sprite(mlx, "desk_clock", x, y);
	}
	else if (elt == 'E')
	{
		render_sprite(mlx, "exit", x, y);		
	}
	else if (elt == 'C')
	{
		render_sprite(mlx, "form_1", x, y);
	}
}

int	draw_map(t_list *map, t_mlx *mlx)
{
	int	x;
	int	y;
	t_list	*iterator;

	y = 0;
	iterator = map;
	mlx->image_width = 0;
	mlx->image_height = 0;
	load_images(mlx);
	draw_background(mlx);
	while (iterator)
	{
		x = 0;
		while (x < mlx->map_length)
		{
			place_elt(map, mlx, x, y, iterator->line[x / mlx->sprite_size]);
			x += mlx->sprite_size;
		}
		iterator = iterator->next;
		y += mlx->sprite_size;
	}
	return (0);
}

void	destroy_sprites(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < SPRITE_COUNT)
		mlx_destroy_image(mlx->mlx_ptr, mlx->sprites[i++].image);
}

int	start_game(t_list *map)
{
	t_list	*iterator;
	t_mlx	mlx;
	t_data	img;
	
	mlx.sprite_size = 112;
	mlx.map_length = (ft_strlen(map->line) - 1) * mlx.sprite_size;
	mlx.map_height = (get_map_height(map)) * mlx.sprite_size;
	mlx.mlx_ptr = mlx_init();
	load_images(&mlx);
	if (!mlx.mlx_ptr)
		return (0);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.map_length, 
		mlx.map_height, "Moonkey");
	draw_map(map, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_redcross, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1, ft_key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_sprites(&mlx);
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
	start_game(map);
	ft_clear(map);
	return (0);
}