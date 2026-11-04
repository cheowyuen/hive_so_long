/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_keyhook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 10:50:10 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	cleanup(t_game *game)
{
	free_c_pos(game->c_pos, game->c_total);
	mlx_delete_image(game->mlx, game->img_g);
	mlx_delete_image(game->mlx, game->img_p);
	mlx_delete_image(game->mlx, game->img_c);
	mlx_delete_image(game->mlx, game->img_w);
	mlx_delete_image(game->mlx, game->img_e);
	mlx_delete_texture(game->ground);
	mlx_delete_texture(game->player);
	mlx_delete_texture(game->coin);
	mlx_delete_texture(game->wall);
	mlx_delete_texture(game->exit);
	mlx_terminate(game->mlx);
	return (-1);
}

static void	collect_coins(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->c_total && game->c_count > 0)
	{
		if (game->c_pos[i][0] == game->img_p->instances[0].x
			&& game->c_pos[i][1] == game->img_p->instances[0].y
			&& game->img_c->instances[i].enabled)
		{
			game->img_c->instances[i].enabled = false;
			game->c_count--;
		}
		i++;
	}
	if (game->img_p->instances[0].x == game->img_e->instances[0].x
		&& game->img_p->instances[0].y == game->img_e->instances[0].y
		&& game->c_count == 0)
		mlx_close_window(game->mlx);
}

static void	move_player(t_game *game, int x_pos, int y_pos)
{
	if (x_pos >= 0)
		game->img_p->instances[0].x = x_pos;
	if (y_pos >= 0)
		game->img_p->instances[0].y = y_pos;
	game->steps++;
	write(1, "step ", 5);
	ft_putnbr_fd(game->steps, 1);
	write(1, "\n", 1);
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		row;
	int		col;

	game = (t_game *) param;
	row = game->img_p->instances[0].y / PIXEL;
	col = game->img_p->instances[0].x / PIXEL;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
	if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS
		&& game->map[row - 1][col] != '1')
		move_player(game, -1, game->img_p->instances[0].y - PIXEL);
	if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS
		&& game->map[row + 1][col] != '1')
		move_player(game, -1, game->img_p->instances[0].y + PIXEL);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS
		&& game->map[row][col - 1] != '1')
		move_player(game, game->img_p->instances[0].x - PIXEL, -1);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS
		&& game->map[row][col + 1] != '1')
		move_player(game, game->img_p->instances[0].x + PIXEL, -1);
	collect_coins(game);
}
