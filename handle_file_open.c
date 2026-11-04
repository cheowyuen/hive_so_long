/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_file_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwong <cwong@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 11:20:39 by cwong             #+#    #+#             */
/*   Updated: 2025/06/17 10:24:19 by cwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_error(const char *error)
{
	write(1, "Error\n", 6);
	write(1, error, ft_strlen(error));
	return (-1);
}

static int	free_buffer(char **buffer)
{
	free(*buffer);
	return (handle_error("File read error\n"));
}

int	read_map_file(int fd, char **buffer)
{
	char		temp[1025];
	ssize_t		bytes_read;
	char		*joined;

	*buffer = ft_strdup("");
	if (!*buffer)
		return (handle_error("Memory allocation failed\n"));
	bytes_read = read(fd, temp, 1024);
	if (bytes_read == -1)
		return (free_buffer(buffer));
	while (bytes_read > 0)
	{
		temp[bytes_read] = '\0';
		joined = ft_strjoin(*buffer, temp);
		free(*buffer);
		if (!joined)
			return (handle_error("Memory allocation failed\n"));
		*buffer = joined;
		bytes_read = read(fd, temp, 1024);
		if (bytes_read == -1)
			return (free_buffer(buffer));
	}
	return (0);
}

static int	has_ber_extension(const char *filepath)
{
	const char	*filename;
	size_t		len;

	filename = ft_strrchr(filepath, '/');
	if (filename)
		filename++;
	else
		filename = filepath;
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".ber", 4) != 0)
		return (handle_error("Map file must have .ber extension\n"));
	return (0);
}

int	handle_file_open(int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (handle_error("Invalid number of arguments\n"));
	if (has_ber_extension(argv[1]) == -1)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (handle_error("Cannot open file\n"));
	return (fd);
}
