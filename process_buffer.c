/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/20 17:11:06 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**allocate_map(int row, int col)
{
	char	**map;
	int		i;

	map = malloc(row * sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	while (i < row)
	{
		map[i] = malloc(col + 1);
		if (!map[i])
		{
			while (i > 0)
				free(map[--i]);
			free(map);
			return (NULL);
		}
		map[i][col] = '\0';
		i++;
	}
	return (map);
}

static int	count_rows(char *ptr)
{
	int		row;
	char	*newline;
	int		i;

	row = 0;
	i = 0;
	while (ptr[i])
	{
		newline = ft_strchr(&ptr[i], '\n');
		if (newline)
		{
			i = (newline - ptr) + 1;
			row++;
		}
		else
		{
			row++;
			break ;
		}
	}
	return (row);
}

static int	count_columns(char *ptr, int *col)
{
	int	i;

	i = 0;
	while (ptr[i] && ptr[i] != '\n')
	{
		(*col)++;
		i++;
	}
	if (*col == 0)
		return (handle_error("Empty line detected\n"));
	return (0);
}

static int	count_map_dimensions(char *buffer, int *row, int *col)
{
	*row = 0;
	*col = 0;
	if (count_columns(buffer, col) == -1)
		return (-1);
	*row = count_rows(buffer);
	return (0);
}

int	process_buffer(char *buffer, char ***map, t_map_info *info)
{
	int			row;
	int			col;

	if (count_map_dimensions(buffer, &row, &col) == -1)
	{
		free(buffer);
		return (-1);
	}
	*map = allocate_map(row, col);
	if (!(*map))
	{
		free(buffer);
		return (handle_error("Memory allocation failed\n"));
	}
	info->row = row;
	info->col = col;
	if (fill_and_validate_map(buffer, *map, info) == -1)
	{
		free(buffer);
		free_map(*map, row);
		return (-1);
	}
	return (0);
}
