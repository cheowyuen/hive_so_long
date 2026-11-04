/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_null.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 09:53:16 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	terminate_mlx(t_game *game)
{
	mlx_terminate(game->mlx);
	return (-1);
}

void	set_null(t_game *game)
{
	game->ground = NULL;
	game->player = NULL;
	game->coin = NULL;
	game->wall = NULL;
	game->exit = NULL;
	game->img_g = NULL;
	game->img_p = NULL;
	game->img_c = NULL;
	game->img_w = NULL;
	game->img_e = NULL;
}
