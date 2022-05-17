/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:04:29 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/17 15:55:07 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/so_long.h"
#include "../ft_printf/ft_printf.h"
#include "../libft/libft.h"
#include "../minilibx-linux/libmlx.h"

//count total number of collectibles in map
int	ft_count_c(t_mlx *mlx)
{
	t_list	*iterator;
	int		count_c;

	count_c = 0;
	iterator = mlx->map;
	while (iterator)
	{
		count_c += ft_count(iterator->line, 'C');
		iterator = iterator->next;
	}
	return (count_c);
}

//initiate mlx, get map size, inititate game, clean up
int	start_game(t_list *map)
{
	t_list	*iterator;
	t_mlx	mlx;
	t_data	img;

	mlx.map = map;
	mlx.win_ptr = NULL;
	mlx.sprites = NULL;
	mlx.sprite_size = get_sprite_size(&mlx);
	mlx.n_collectibles = ft_count_c(&mlx);
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
	t_list	*map;

	map = NULL;
	if (argc != 2)
		ft_panic(WRONG_NARG, 0, &map);
	map = ft_parse(argv[1]);
	start_game(map);
	if (!start_game)
	{
		ft_clear(&map);
		return (-8);
	}
	return (0);
}
