/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 17:56:06 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/19 10:13:03 by amarchan         ###   ########.fr       */
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
		free_mlx(mlx);
		exit(EXIT_FAILURE);
	}
	return (output);
}

char	*choose_sprite_size(t_mlx *mlx)
{
	int			fd;
	static char	*line;

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
		return (line);
	}
	return (NULL);
}

char	**ft_read_sprites_tab(t_mlx *mlx)
{
	char		**file_loc;
	char		*temp;
	int			line;

	line = -1;
	file_loc = malloc(sizeof(char *) * 9);
	if (!file_loc)
	{
		free_mlx(mlx);
		ft_panic(MALLOC_FAILURE, 0, 0);
	}
	ft_bzero(file_loc, sizeof(char *) * 9);
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
	return (file_loc);
}

//place all pointers to sprites in arr and male mlx->sprites point to arr.
void	sort_sprites_in_tab(t_mlx *mlx)
{
	t_sprite	*arr;
	char		**file_loc;

	mlx->sprites = NULL;
	file_loc = ft_read_sprites_tab(mlx);
	arr = malloc(sizeof(t_sprite) * SPRITE_COUNT);
	if (!arr)
		ft_clean_arr(mlx, file_loc);
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
	free(file_loc);
}
