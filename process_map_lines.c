/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_map_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 09:53:13 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	process_char_and_update_info(char c, t_map_info *info, int row
	, int col)
{
	if (c == 'C')
		info->c_count++;
	else if (c == 'E')
		info->e_count++;
	else if (c == 'P')
	{
		info->p_count++;
		info->player_x = row;
		info->player_y = col;
	}
	else if (c != '0' && c != '1')
	{
		return (handle_error("Map can only contain the characters '0', '1'"
				", 'C', 'E', and 'P'\n"));
	}
	return (0);
}

static int	check_wall_and_shape_rules(char *ptr, t_map_info *info, int len)
{
	int	i;

	if (len != info->col)
		return (handle_error("Map must be rectangular\n"));
	i = 0;
	while (ptr[i])
	{
		if (info->is_first_row && ptr[i] != '1')
			return (handle_error("Top row must be all walls ('1')\n"));
		if (info->is_last_row && ptr[i] != '1')
			return (handle_error("Bottom row must be all walls ('1')\n"));
		if ((i == 0 || i == len - 1) && ptr[i] != '1')
		{
			return (handle_error("Each row must start and end with a"
					" wall ('1')\n"));
		}
		i++;
	}
	return (0);
}

static int	process_line(char *ptr, char *map, t_map_info *info, int row)
{
	int	col;
	int	len;

	len = ft_strlen(ptr);
	if (len == 0)
		return (handle_error("Empty line detected\n"));
	if (check_wall_and_shape_rules(ptr, info, len) == -1)
		return (-1);
	col = 0;
	while (ptr[col])
	{
		if (process_char_and_update_info(ptr[col], info, row, col) == -1)
			return (-1);
		map[col] = ptr[col];
		col++;
	}
	info->is_first_row = 0;
	return (0);
}

int	process_map_lines(char *ptr, char **map, t_map_info *info)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		newline = ft_strchr(&ptr[i], '\n');
		if (newline)
			*newline = '\0';
		if (j == info->row - 1)
			info->is_last_row = 1;
		if (process_line(&ptr[i], map[j], info, j) == -1)
			return (-1);
		if (newline)
			i = (newline - ptr) + 1;
		else
			i += ft_strlen(&ptr[i]);
		j++;
	}
	return (0);
}
