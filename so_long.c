/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 15:40:23 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, int row)
{
	int	i;

	i = 0;
	while (i < row)
		free(map[i++]);
	free(map);
}

int	main(int argc, char **argv)
{
	int			fd;
	char		*buffer;
	char		**map;
	t_map_info	info;

	map = NULL;
	fd = handle_file_open(argc, argv);
	if (fd < 0)
		return (-1);
	if (read_map_file(fd, &buffer) == -1)
	{
		close(fd);
		return (-1);
	}
	close(fd);
	info = (t_map_info){1, 0, 0, 0, 0, 0, 0, 0, 0};
	if (process_buffer(buffer, &map, &info) == -1)
		return (-1);
	free(buffer);
	if (init_and_run_game(map, &info) == -1)
		return (-1);
	free_map(map, info.row);
	return (0);
}
