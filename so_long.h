/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 09:53:18 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"

# ifndef PIXEL
#  define PIXEL 64
# endif

typedef struct s_map_info
{
	int	is_first_row;
	int	is_last_row;
	int	col;
	int	row;
	int	c_count;
	int	e_count;
	int	p_count;
	int	player_x;
	int	player_y;
}	t_map_info;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_game
{
	char			**map;
	t_point			size;
	int				c_count;
	int				c_total;
	int				**c_pos;
	int				steps;
	mlx_t			*mlx;
	mlx_texture_t	*ground;
	mlx_texture_t	*player;
	mlx_texture_t	*coin;
	mlx_texture_t	*wall;
	mlx_texture_t	*exit;
	mlx_image_t		*img_g;
	mlx_image_t		*img_p;
	mlx_image_t		*img_c;
	mlx_image_t		*img_w;
	mlx_image_t		*img_e;
}	t_game;

int		handle_file_open(int argc, char **argv);
int		handle_error(const char *error);
int		read_map_file(int fd, char **buffer);
int		process_buffer(char *buffer, char ***map, t_map_info *info);
int		fill_and_validate_map(char *ptr, char **map, t_map_info *info);
int		process_map_lines(char *ptr, char **map, t_map_info *info);
int		init_and_run_game(char **map, t_map_info *info);
int		render_game(t_game *game);
void	my_keyhook(mlx_key_data_t keydata, void *param);
int		cleanup(t_game *game);
void	free_map(char **map, int row);
int		free_c_pos(int **c_pos, int row);
int		terminate_mlx(t_game *game);
void	set_null(t_game *game);

#endif
