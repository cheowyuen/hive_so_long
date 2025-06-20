/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_run_game.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 09:53:09 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	render_background(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->size.x)
	{
		j = 0;
		while (j < game->size.y)
		{
			if (game->map[i][j] == '1')
			{
				if (mlx_image_to_window(game->mlx, game->img_w, j * PIXEL
						, i * PIXEL) < 0)
					return (handle_error(mlx_strerror(mlx_errno)));
			}
			else if (mlx_image_to_window(game->mlx, game->img_g, j * PIXEL
					, i * PIXEL) < 0)
				return (handle_error(mlx_strerror(mlx_errno)));
			j++;
		}
		i++;
	}
	return (0);
}

static int	alloc_c_pos(t_game *game)
{
	int	i;

	game->c_pos = malloc(sizeof(int *) * game->c_count);
	if (!game->c_pos)
		return (handle_error("Memory allocation failed"));
	i = 0;
	while (i < game->c_count)
	{
		game->c_pos[i] = malloc(sizeof(int) * 2);
		if (!game->c_pos[i])
		{
			while (--i >= 0)
				free(game->c_pos[i]);
			free(game->c_pos);
			return (handle_error("Memory allocation failed"));
		}
		i++;
	}
	return (0);
}

static int	load_images(t_game *game)
{
	game->ground = mlx_load_png("images/ground.png");
	game->player = mlx_load_png("images/player.png");
	game->coin = mlx_load_png("images/coin.png");
	game->wall = mlx_load_png("images/wall.png");
	game->exit = mlx_load_png("images/exit.png");
	if (!game->ground || !game->player || !game->coin || !game->wall
		|| !game->exit)
		return (handle_error(mlx_strerror(mlx_errno)));
	game->img_g = mlx_texture_to_image(game->mlx, game->ground);
	game->img_p = mlx_texture_to_image(game->mlx, game->player);
	game->img_c = mlx_texture_to_image(game->mlx, game->coin);
	game->img_w = mlx_texture_to_image(game->mlx, game->wall);
	game->img_e = mlx_texture_to_image(game->mlx, game->exit);
	if (!game->img_g || !game->img_p || !game->img_c || !game->img_w
		|| !game->img_e)
		return (handle_error(mlx_strerror(mlx_errno)));
	return (0);
}

static int	init_game(char **map, t_map_info *info, t_game *game)
{
	int32_t	width;
	int32_t	height;

	game->map = map;
	game->size = (t_point){info->row, info->col};
	game->c_count = info->c_count;
	game->c_total = info->c_count;
	game->steps = 0;
	game->mlx = mlx_init(info->col * PIXEL, info->row * PIXEL, "so_long",
			false);
	if (!game->mlx)
		return (handle_error(mlx_strerror(mlx_errno)));
	mlx_get_monitor_size(0, &width, &height);
	if (info->col * PIXEL > width || info->row * PIXEL > height)
		return (handle_error("Map is too big for the screen\n"));
	set_null(game);
	if (alloc_c_pos(game) == -1)
		return (terminate_mlx(game));
	if (load_images(game) == -1)
		return (cleanup(game));
	if (render_background(game) == -1)
		return (cleanup(game));
	if (render_game(game) == -1)
		return (cleanup(game));
	return (0);
}

int	init_and_run_game(char **map, t_map_info *info)
{
	t_game	game;

	if (init_game(map, info, &game) == -1)
	{
		free_map(map, info->row);
		return (-1);
	}
	mlx_key_hook(game.mlx, &my_keyhook, &game);
	mlx_loop(game.mlx);
	cleanup(&game);
	return (0);
}
