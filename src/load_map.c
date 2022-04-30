/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:56:06 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/01 00:38:17 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

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
	t_sprite	output;

	output.image = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&mlx->image_width, &mlx->image_height);
	output.name = name;
	if (!output.image)
	{
		destroy_sprites(mlx);
		ft_clear(mlx->map);
		free_mlx(mlx);
		exit(EXIT_FAILURE);
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
	arr[0] = load_sprite(mlx, "./media/background_1_112x112.xpm", "bg");
	arr[1] = load_sprite(mlx, "./media/bleak_desk_clock_112x112.xpm",
			"desk_clock");
	arr[2] = load_sprite(mlx, "./media/bleak_desk_pile_of_death_112x112.xpm",
			"desk_pile");
	arr[3] = load_sprite(mlx, "./media/bleak_desk_poison_water_112x112.xpm",
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
	static int	i = 1;

	if (elt == 'P')
	{
		render_sprite(mlx, "moonkey", x, y);
		mlx->player_x = x;
		mlx->player_y = y;
	}
	else if (elt == '1')
	{
		if (i == 1)
			render_sprite(mlx, "desk_clock", x, y);
		else if (i == 2)
			render_sprite(mlx, "desk_pile", x, y);
		else if (i == 3)
			render_sprite(mlx, "desk_poison", x, y);
		if (i == 3)
			i = 0;
		i++;
	}
	else if (elt == 'E')
		render_sprite(mlx, "exit", x, y);
	else if (elt == 'C')
		render_sprite(mlx, "form_1", x, y);
}

//browse map given in argument and initiate drawing
int	draw_map(t_list *map, t_mlx *mlx)
{
	int		x;
	int		y;
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
