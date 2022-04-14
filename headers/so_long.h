/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 13:58:56 by amarchan          #+#    #+#             */
/*   Updated: 2022/04/14 12:16:27 by amarchan         ###   ########.fr       */
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
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"

#define WRONG_NARG -1
#define INVALID_ARG -2
#define MALLOC_FAILURE -3

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
	int		x;
	int		y;
}	t_mlx;

int		ft_panic(int errcode, int i);
t_list	*ft_parse(char *argv);
void	ft_clear(t_list *lst);

#endif