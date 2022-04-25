/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:56 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/25 16:14:24 by amarchan         ###   ########.fr       */
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

#define WRONG_NARG -1
#define INVALID_ARG -2
#define INVALID_NARG -3
#define MALLOC_FAILURE -4
#define ISNOT_REC -5
#define EMPTY_LINE -6
#define HOLE_WALL -7

#define ESC_KEYCODE 65307
#define UP 119
#define DOWN 115
#define LEFT 97
#define RIGHT 100

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*image;
	int		sprite_size;
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

//parsing
int		ft_panic(int errcode, int i);
t_list	*ft_parse(char *argv);
int		ft_count(char *str, char c);
int		line_is_wall(char *str);
int		col_is_wall(char *str);
int		check_char(char *str);
int		ft_check_walls(t_list *lst);
int		is_rectangular(t_list *lst);
int		ft_row_length(const char *s);
t_list	*ft_read_map(char *argv);
int		ft_count_elts(t_list *lst);
int		ft_check_elts(t_list *lst);
void	ft_print_lst(t_list *lst);
t_list	*ft_create_list(char *line);
int		ft_count_elts(t_list *lst);
int		is_rectangular(t_list *lst);
int		ft_row_length(const char *s);

//clean up
void	ft_clear(t_list *lst);

#endif