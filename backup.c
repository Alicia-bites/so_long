void	sort_sprites_in_tab(t_mlx *mlx)
{
	t_sprite	*arr;
	char		*file_loc;
	
	file_loc = get_sprite_size(mlx);
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