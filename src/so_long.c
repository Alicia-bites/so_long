/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:04:29 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/28 17:45:58 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

//close window
int	ft_redcross(t_mlx *mlx)
{
	printf("Leaving the game. See you later!\n");
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

//put player on the screen
void ft_render_player(t_mlx *mlx)
{
	render_sprite(mlx, "moonkey", mlx->player_x, mlx->player_y);
}

//clean up screen for player to move around
void ft_clear_player(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->sprites->image, 
		mlx->player_x, mlx->player_y);
}

t_list	*get_pos_right_left(t_mlx *mlx)
{
	t_list	*iterator;

	iterator = mlx->map;
	while (iterator->next)
	{	
		if (iterator->index == mlx->player_y / mlx->sprite_size)
			break;
		iterator = iterator->next;
	}
	return (iterator);
}

t_list	*get_pos_down(t_mlx *mlx)
{
	t_list	*iterator;

	iterator = mlx->map;
	while (iterator)
	{	
		if (iterator->index == (mlx->player_y + mlx->sprite_size)
				/ mlx->sprite_size)
			break;
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
			break;
		iterator = iterator->next;
	}
	return(iterator);
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

int	can_go(t_mlx *mlx, int keycode)
{
	t_list	*y;

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

//define how player move around
int	ft_key_hook(int keycode, t_mlx *mlx)
{
	if (keycode != ESC_KEYCODE)
	{				
		if (keycode == UP || keycode == DOWN || keycode == LEFT
			|| keycode == RIGHT)
		{
			ft_clear_player(mlx);
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
		ft_redcross(mlx);
	return (keycode);
}

//put pixels in windows
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

//compute map height
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
	return (map_height + 1);
}

//open background image and display in window
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
			render_sprite(mlx, "bg", x, y);
			y += mlx->sprite_size;
		}
		x += mlx->sprite_size;
	}
}

//display sprites on window
void	render_sprite(t_mlx *mlx, char *name, int x, int y)
{
	int	i;

	i = 0;
	while (i < SPRITE_COUNT)
	{
		if (ft_strcmp(name, mlx->sprites[i].name) == 0)
		{
			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, 
				mlx->sprites[i].image, x, y);
			return ;
		}
		i++;
	}
}

//load sprites
t_sprite	load_sprite(t_mlx *mlx, char *path, char *name)
{
	t_sprite output;

	output.image = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
		&mlx->image_width, &mlx->image_height);
	output.name = name;
	printf("output.image = %p\n", output.image);
	if (!output.image)
	{
		destroy_sprites(mlx);
		ft_clear(mlx->map);
		free_mlx(mlx);
		exit(EXIT_FAILURE); // TODO : Quitter et liberer la mlx et les sprites
	}
	return (output);
}

//place all pointers to sprites in arr and male mlx->sprites point to arr.
void	sort_sprites_in_tab(t_mlx *mlx)
{
	t_sprite	*arr;

	arr = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	ft_bzero(arr, sizeof(t_sprite) * SPRITE_COUNT);
	mlx->sprites = arr;
	// arr[0] = load_sprite(mlx, "./media/background_1_112x112.xpm", "bg");	
	arr[0] = load_sprite(mlx, "./media/background_1_112x112.xpm", "bg");
	arr[1] = load_sprite(mlx, "./media/bleak_desk_clock_112x112.xpm",
		"desk_clock");
	arr[2] = load_sprite(mlx, "./media/bleak_desk_pile_of_death_112x112.xpm",
		"desk_pile");
	arr[3] = load_sprite(mlx, "./media/bleak_desk_poison_wate_112x112.xpm",
		"desk_poison");
	arr[4] = load_sprite(mlx, "./media/exit_112x112.xpm", "exit");
	arr[5] = load_sprite(mlx, "./media/form_1_112x112.xpm", "form_1");
	arr[6] = load_sprite(mlx, "./media/form_2_112x112.xpm", "form_2");
	arr[7] = load_sprite(mlx, "./media/form_3_112x112.xpm", "form_3");
	arr[8] = load_sprite(mlx, "./media/moonkey_112x112.xpm", "moonkey");	
}

//place map elts in winodw
void	place_elt(t_mlx *mlx, int x, int y, int elt)
{
	if (elt == 'P')
	{
		render_sprite(mlx, "moonkey", x, y);
		mlx->player_x = x;
		mlx->player_y = y;
	}
		// move_player(map, mlx, x, y);
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

//browse map given in argument and initiate drawing
int	draw_map(t_list *map, t_mlx *mlx)
{
	int	x;
	int	y;
	t_list	*iterator;

	y = 0;
	iterator = map;
	mlx->image_width = 0;
	mlx->image_height = 0;
	draw_background(mlx);
	while (iterator)
	{
		x = 0;
		while (x < mlx->map_length)
		{
			place_elt(mlx, x, y, iterator->line[x / mlx->sprite_size]);
			x += mlx->sprite_size;
		}
		iterator = iterator->next;
		y += mlx->sprite_size;
	}
	return (0);
}

//initiate mlx, get map size, inititate game, clean up
int	start_game(t_list *map)
{
	t_list	*iterator;
	t_mlx	mlx;
	t_data	img;
	
	mlx.map = map;
	mlx.sprite_size = 112;
	mlx.map_length = (ft_strlen(map->line) - 1) * mlx.sprite_size;
	mlx.map_height = (get_map_height(map)) * mlx.sprite_size;
	mlx.mlx_ptr = mlx_init();
	if (!mlx.mlx_ptr)
		return (0);
	sort_sprites_in_tab(&mlx);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.map_length, 
		mlx.map_height, "Moonkey");
	draw_map(map, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_redcross, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1, ft_key_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_sprites(&mlx);
	free_mlx(&mlx);
	return (1);
}

int	main(int argc, char **argv)
{
	t_list *map;
	
	map = NULL;
	if (argc != 2)
		return (ft_panic(WRONG_NARG, 0));
	map = ft_parse(argv[1]);
	start_game(map);
	if (!start_game)
	{
		ft_clear(map);
		return (-8);
	}
	ft_clear(map);
	return (0);
}