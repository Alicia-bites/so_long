#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../minilibx-linux/libmlx.h"

#define ESC_KEYCODE 65307
#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100

typedef struct s_mlx // Pour passer ce qu'on veut aux events (hook) MLX
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	int		x;
	int		y;
}	t_mlx;

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;


void	free_mlx(t_mlx mlx)
{
	printf("Je free %p et %p\n", mlx.mlx_ptr, mlx.win_ptr);
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr); // alors on a la detruit apres avec arreter la loop
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
}

int	ft_redcross(t_mlx *mlx)
{
	printf("Leaving game. See you later!\n");
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

int main()
{
	t_mlx	mlx;
	t_data	img;
	int		i;
	int		j;

	i = 0;
	j = 0;
	// printf("MLX : %p\n", mlx_ptr);
	// void *window = mlx_new_window(mlx_ptr, 250, 250, "aliciamlx");
	// if (!window)
	// 	return (1);
	// // Structure MLX pour pouvoir fermer a tout moment ou manipuler
	// 		// la fenetre ou meme le joueur etc.
	// mlx.mlx_ptr = mlx_ptr;
	// mlx.win_ptr = window;
	
	// printf("MLX window : %p\n", window);
	// mlx_hook(window, 17, 0, ft_redcross, &mlx);
	

	// // Un autre carre de 100 sur 100
	// for (size_t i = 100; i < 200; i++)
	// {
	// 	for (size_t j = 100; j < 200; j++)
	// 	{
	// 		mlx_pixel_put(mlx.mlx_ptr, mlx.win_ptr, i, j, 0x0C0FFEE);
	// 	}
	// }
	// mlx_loop(mlx_ptr);
	// // La croix rouge (ou ESC sur so_long) doit seulement couper la boucle
	// printf("Oh la boucle est terminee\n");
	// free_mlx(mlx);
	// La sale gueule d'Alicia
	mlx.mlx_ptr = mlx_init();
	printf("mlx.mlx_ptr : %p\n", mlx.mlx_ptr);
	if (!mlx.mlx_ptr)
		return (1);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1000, 1000, "moonkey"); // peut etre null
	
	// Carre de 100 sur 100
	img.img = mlx_new_image(mlx.mlx_ptr, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, 
		&img.line_length, &img.endian);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			my_mlx_pixel_put(&img, i, j, 0x00FF5733);
		}												//  ^^^^^^^^
														//  aarrggbb
	}
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, img.img, i, j);
	
	// Charger une image
	int image_width, image_height = 0;
	mlx.image = mlx_xpm_file_to_image(mlx.mlx_ptr, "./../media/form_1_48x48.xpm", &image_width, &image_height); // peut etre null
	printf("J'ai charge une image de taille %dx%d\n", image_width, image_height);
	mlx.y = 250;
	mlx.x = 250;

	// while (x < 1010-460)
	// {
	// 	while (y < 1010-460)
	// 	{
	// 		mlx_put_image_to_window(mlx_ptr, window, image, y, x);
	// 		usleep(51000);
	// 		y += 100;
	// 	}
	// 	x += 80;
	// 	y = 0;
	// }

	// ft_render_player(&mlx);
	mlx_hook(mlx.win_ptr, 17, 0, ft_redcross, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1, ft_key_hook, &mlx);
	//	              key ^  ^ pressed (man X11)
	mlx_loop(mlx.mlx_ptr);

	// On se debarasse de l'image
	mlx_destroy_image(mlx.mlx_ptr, mlx.image);
	free_mlx(mlx);
	return (0);
}
