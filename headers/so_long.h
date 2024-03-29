/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:56 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/19 10:14:43 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include "../minilibx-linux/libmlx.h"
# include "../libft/libft.h"

# define WRONG_NARG -1
# define INVALID_ARG -2
# define INVALID_NARG -3
# define MALLOC_FAILURE -4
# define ISNOT_REC -5
# define EMPTY_LINE -6
# define HOLE_WALL -7
# define PTR_FAIL -8
# define FILE_ERROR -9

# define ESC_KEYCODE 65307
# define UP 119
# define DOWN 115
# define LEFT 97
# define RIGHT 100

# define SPRITE_COUNT 9

typedef struct s_sprite
{
	void	*image;
	char	*name;
}	t_sprite;

typedef struct s_mlx
{
	t_list		*map;
	int			image_height;
	int			image_width;
	int			row_length;
	int			col_height;
	int			map_height;
	int			map_length;
	int			sprite_size;
	int			n_collectibles;
	int			player_x;
	int			player_y;
	t_sprite	*sprites;
	void		*image;
	void		*mlx_ptr;
	void		*player;
	void		*win_ptr;
}	t_mlx;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

//parsing
void		ft_panic(int errcode, int i, t_list **lst);
t_list		*ft_parse(char *argv);
int			ft_count(char *str, char c);
int			line_is_wall(char *str);
int			col_is_wall(char *str);
int			check_char(char *str);
int			ft_check_walls(t_list *lst);
int			ft_row_length(const char *s);
t_list		*ft_read_map(char *argv);
int			ft_count_elts(t_list *lst);
int			ft_check_elts(t_list *lst);
void		ft_print_lst(t_list *lst);
t_list		*ft_create_list(char *line);
int			ft_count_elts(t_list *lst);
void		is_rectangular(t_list *lst);
int			ft_row_length(const char *s);
int			wrong_file(char *str);

//so_long
int			start_game(t_list *map);

//draw_map
int			draw_map(t_list *map, t_mlx *mlx);
void		place_elt(t_mlx *mlx, int x, int y, int elt);
void		place_collectibles(t_mlx *mlx, int x, int y);
void		place_wall(t_mlx *mlx, int x, int y);

//load_map
void		sort_sprites_in_tab(t_mlx *mlx);
char		**ft_read_sprites_tab(t_mlx *mlx);
char		*choose_sprite_size(t_mlx *mlx);
t_sprite	load_sprite(t_mlx *mlx, char *path, char *name);
void		render_sprite(t_mlx *mlx, char *name, int x, int y);

//load_map_2
void		draw_background(t_mlx *mlx);
int			get_map_height(t_list *map);

//sprite_size
int			get_sprite_size(t_mlx *mlx);
void		get_map_dimensions(t_mlx *mlx);

//move_player
int			ft_key_hook(int keycode, t_mlx *mlx);
void		move_player(t_mlx *mlx, int keycode, int collectibles);
t_list		*get_y(t_mlx *mlx, int keycode);
int			can_go(t_mlx *mlx, int keycode);

//move_player_2
t_list		*get_y_right_left(t_mlx *mlx);
t_list		*get_y_up(t_mlx *mlx);
t_list		*get_y_down(t_mlx *mlx);
void		ft_clear_player(t_mlx *mlx);
void		ft_render_player(t_mlx *mlx);

//collect_and_exit
int			handle_collec(t_mlx *mlx, int collectibles);
void		found_exit(t_mlx *mlx, int collectibles);
int			is_exit(t_mlx *mlx, int keycode);
int			is_collectible(t_mlx *mlx, int keycode);

//mlx_utils
int			ft_redcross(t_mlx *mlx, int x);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//clean up
void		ft_clear(t_list **lst);
void		destroy_sprites(t_mlx *mlx);
void		free_mlx(t_mlx *mlx);
void		ft_clear_file_loc(char **tab);
void		ft_clean_arr(t_mlx *mlx, char **file_loc);

#endif