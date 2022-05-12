/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:56 by amarchan          #+#    #+#             */
/*   Updated: 2022/05/04 19:57:45 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdio.h>
# include <string.h>
# include <limits.h>
# include <sys/types.h>
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
	int			map_height;
	int			map_length;
	int			sprite_size;
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
int			ft_panic(int errcode, int i);
t_list		*ft_parse(char *argv);
int			ft_count(char *str, char c);
int			line_is_wall(char *str);
int			col_is_wall(char *str);
int			check_char(char *str);
int			ft_check_walls(t_list *lst);
int			is_rectangular(t_list *lst);
int			ft_row_length(const char *s);
t_list		*ft_read_map(char *argv);
int			ft_count_elts(t_list *lst);
int			ft_check_elts(t_list *lst);
void		ft_print_lst(t_list *lst);
t_list		*ft_create_list(char *line);
int			ft_count_elts(t_list *lst);
int			is_rectangular(t_list *lst);
int			ft_row_length(const char *s);

//so_long
int			start_game(t_list *map);

//load_map
int			draw_map(t_list *map, t_mlx *mlx);
void		place_elt(t_mlx *mlx, int x, int y, int elt);
void		sort_sprites_in_tab(t_mlx *mlx);
t_sprite	load_sprite(t_mlx *mlx, char *path, char *name);
void		render_sprite(t_mlx *mlx, char *name, int x, int y);
void		draw_background(t_mlx *mlx);
int			get_map_height(t_list *map);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//move_player
int			ft_key_hook(int keycode, t_mlx *mlx);
int			can_go(t_mlx *mlx, int keycode);
t_list		*get_y(t_mlx *mlx, int keycode);
t_list		*get_pos_up(t_mlx *mlx);
t_list		*get_pos_down(t_mlx *mlx);
void		ft_clear_player(t_mlx *mlx);
void		ft_render_player(t_mlx *mlx);

//move_player_2
t_list		*get_pos_right_left(t_mlx *mlx);
void		ft_render_player(t_mlx *mlx);

//mlx_utils
int			ft_redcross(t_mlx *mlx, int x);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//clean up
void		ft_clear(t_list *lst);
void		destroy_sprites(t_mlx *mlx);
void		free_mlx(t_mlx *mlx);

#endif