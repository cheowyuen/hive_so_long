/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 09:53:14 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	free_c_pos(int **c_pos, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(c_pos[i++]);
	free(c_pos);
	return (-1);
}

static int	render_coins(t_game *game, int i, int j, int *k)
{
	if (mlx_image_to_window(game->mlx, game->img_c, j * PIXEL, i * PIXEL) < 0)
		return (handle_error((char *) mlx_strerror(mlx_errno)));
	game->c_pos[*k][0] = j * PIXEL;
	game->c_pos[*k][1] = i * PIXEL;
	(*k)++;
	return (0);
}

int	render_game(t_game *game)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (i < game->size.x)
	{
		j = 0;
		while (j < game->size.y)
		{
			if (game->map[i][j] == 'P' && mlx_image_to_window(game->mlx
				, game->img_p, j * PIXEL, i * PIXEL) < 0)
				return (handle_error((char *) mlx_strerror(mlx_errno)));
			else if (game->map[i][j] == 'C'
				&& render_coins(game, i, j, &k) == -1)
				return (-1);
			else if (game->map[i][j] == 'E' && mlx_image_to_window(game->mlx
				, game->img_e, j * PIXEL, i * PIXEL) < 0)
				return (handle_error((char *) mlx_strerror(mlx_errno)));
			j++;
		}
		i++;
	}
	return (0);
}
