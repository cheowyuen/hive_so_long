/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_and_validate_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 09:59:24 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	validate_reachability(char **map, t_point size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size.x)
	{
		j = 0;
		while (j < size.y)
		{
			if (map[i][j] == 'C')
			{
				return (handle_error("Not all collectibles ('C') are"
						" reachable from the player's start position\n"));
			}
			if (map[i][j] == 'E')
			{
				return (handle_error("Exit ('E') is not reachable from"
						" the player's start position\n"));
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	fill(char **map, t_point size, t_point cur)
{
	if (cur.y < 0 || cur.y >= size.y - 1 || cur.x < 1 || cur.x >= size.x - 1
		|| map[cur.x][cur.y] == '1' || map[cur.x][cur.y] == 'F')
		return ;
	map[cur.x][cur.y] = 'F';
	fill(map, size, (t_point){cur.x - 1, cur.y});
	fill(map, size, (t_point){cur.x + 1, cur.y});
	fill(map, size, (t_point){cur.x, cur.y - 1});
	fill(map, size, (t_point){cur.x, cur.y + 1});
}

static char	**copy_map(char **map, int row)
{
	char	**fill_map;
	int		i;

	fill_map = malloc(sizeof(char *) * row);
	if (!fill_map)
		return (NULL);
	i = 0;
	while (i < row)
	{
		fill_map[i] = ft_strdup(map[i]);
		if (!fill_map[i])
		{
			while (--i >= 0)
				free(fill_map[i]);
			free(fill_map);
			return (NULL);
		}
		i++;
	}
	return (fill_map);
}

static int	validate_required_elements(t_map_info *info)
{
	if (info->c_count <= 0)
		return (handle_error("Map must contain at least one collectible "
				"('C')\n"));
	if (info->e_count != 1)
		return (handle_error("Map must contain exactly one exit ('E')\n"));
	if (info->p_count != 1)
		return (handle_error("Map must contain exactly one player's start "
				"position ('P')\n"));
	return (0);
}

int	fill_and_validate_map(char *buffer, char **map, t_map_info *info)
{
	t_point		size;
	t_point		p_pos;
	char		**fill_map;

	fill_map = NULL;
	if (process_map_lines(buffer, map, info) == -1)
		return (-1);
	if (validate_required_elements(info) == -1)
		return (-1);
	fill_map = copy_map(map, info->row);
	if (!fill_map)
		return (handle_error("Memory allocation failed\n"));
	size = (t_point){info->row, info->col};
	p_pos = (t_point){info->player_x, info->player_y};
	fill(fill_map, size, p_pos);
	if (validate_reachability(fill_map, size) == -1)
	{
		free_map(fill_map, size.x);
		return (-1);
	}
	free_map(fill_map, size.x);
	return (0);
}
