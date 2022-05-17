/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:56:06 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/17 19:16:05 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"
#include "../headers/get_next_line.h"

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
		// ft_clear(mlx->map);
		free_mlx(mlx);
		exit(EXIT_FAILURE);
	}
	return (output);
}

char	*choose_sprite_size(t_mlx *mlx)
{
	int			fd;
	static char	*line;

	// ft_printf("sprite size = %d\n", mlx->sprite_size);
	if (mlx->sprite_size == 112)
		fd = open("./media/images_112.tbl", O_RDONLY);
	if (mlx->sprite_size == 80)
		fd = open("./media/images_80.tbl", O_RDONLY);
	if (mlx->sprite_size == 64)
		fd = open("./media/images_64.tbl", O_RDONLY);
	if (mlx->sprite_size == 48)
		fd = open("./media/images_48.tbl", O_RDONLY);
	if (mlx->sprite_size == 32)
		fd = open("./media/images_32.tbl", O_RDONLY);
	line = "start";
	while (line != NULL)
	{
		line = get_next_line(fd);
		// ft_printf("line : %s", line);
		return (line);
	}
}
//place all pointers to sprites in arr and male mlx->sprites point to arr.
void	sort_sprites_in_tab(t_mlx *mlx)
{
	t_sprite	*arr;
	char		*file_loc[8];
	char		*temp;
	int			line;
	
	line = -1;
	mlx->sprites = NULL;
	while (file_loc != NULL && line++ <= 7)
	{
		temp = choose_sprite_size(mlx);
		file_loc[line] = ft_strdup(temp);
		free(temp);
		if (!file_loc[line])
		{
			free_mlx(mlx);
			ft_panic(MALLOC_FAILURE, 0, 0);
		}
	}
	arr = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	if (!arr)
	{
		free_mlx(mlx);
		ft_clear_file_loc(file_loc);
		ft_panic(MALLOC_FAILURE, 0, 0);
	}
	ft_bzero(arr, sizeof(t_sprite) * SPRITE_COUNT);
	mlx->sprites = arr;
	arr[0] = load_sprite(mlx, file_loc[0], "bg");
	arr[1] = load_sprite(mlx, file_loc[1], "desk_clock");
	arr[2] = load_sprite(mlx, file_loc[2], "desk_pile");
	arr[3] = load_sprite(mlx, file_loc[3], "desk_poison");
	arr[4] = load_sprite(mlx, file_loc[4], "exit");
	arr[5] = load_sprite(mlx, file_loc[5], "form_1");
	arr[6] = load_sprite(mlx, file_loc[6], "form_2");
	arr[7] = load_sprite(mlx, file_loc[7], "form_3");
	arr[8] = load_sprite(mlx, file_loc[8], "moonkey");
	ft_clear_file_loc(file_loc);
}

void	place_wall(t_mlx *mlx, int x, int y)
{
	static int	i = 1;

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

void	place_collectibles(t_mlx *mlx, int x, int y)
{
	static int	i = 1;

	if (i == 1)
		render_sprite(mlx, "form_1", x, y);
	else if (i == 2)
		render_sprite(mlx, "form_2", x, y);
	else if (i == 3)
		render_sprite(mlx, "form_3", x, y);
	if (i == 3)
		i = 0;
	i++;
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
		place_wall(mlx, x, y);
	else if (elt == 'E')
		render_sprite(mlx, "exit", x, y);
	else if (elt == 'C')
		place_collectibles(mlx, x, y);
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
