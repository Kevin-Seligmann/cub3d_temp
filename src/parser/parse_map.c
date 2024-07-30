/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 04:11:11 by kseligma          #+#    #+#             */
/*   Updated: 2024/07/30 15:43:58 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cubed.h"
# include "parser.h"

// Allocates memory for the map, a doble array
int	alloc_map(t_sim *map)
{
	unsigned int height;

	map->map = malloc(sizeof(*(map->map)) * (map->height + 1));
	if (!map->map)
		return (print_error(-1, MEMORY_ERROR, 0));
	height = 0;
	while (height < map->height)
	{
		map->map[height] = malloc(sizeof(map->map[height]) * (map->width + 1));
		if (!map->map[height])
		{
			map->map[height] = NULL;
			ft_arr_free_int(map->map);
			return (print_error(-1, MEMORY_ERROR, 0));
		}
		height ++;
	}
	map->map[height] = NULL;
	return (0);
}

// Counts the width and height of the map
int	get_dimensions(t_cube *data, char *line)
{
	unsigned int	map_width_aux;

	data->sim.height = 1;
	data->sim.width = ft_strlen(line) - 1;
	map_width_aux = 0;
	while (read_next_line(data->files.fd, &line))
	{
		if (is_map_line(line))
		{
			data->sim.height ++;
			map_width_aux = ft_strlen(line) - 1;
			if (map_width_aux > data->sim.width)
				data->sim.width = map_width_aux;
		}
		else
		{
			free(line);
			return print_error(-1, WRONG_LINE_CONTENT, "Map");
		}
	}
	close(data->files.fd);
	return (0);
}

// Copies the content of map in the file to a doble array
void	copy_map(t_cube *data, int **map, char *line)
{
	unsigned int	width;
	unsigned int	height;

	height = 0;
	while (map[height])
	{
		width = 0;
		while (line[width])
		{
			if (line[width] == '\n')
				map[height][width] = ' ';
			else
				map[height][width] = line[width];
			width ++;
		}
		while (width < data->sim.width)
		{
			map[height][width] = ' ';
			width ++;
		}
		map[height][width] = 0;
		height ++;
		read_next_line(data->files.fd, &line);
	}
}

// Parses the MAP
int	parse_map(t_cube *data, char *line)
{
	if (get_dimensions(data, line) == -1)
		return (-1);
	if (alloc_map(&data->sim) == -1)
		return (-1);
	if (open_file(data->files.config_file_path, &data->files.fd) == -1)
		return (-1);
	line = NULL;
	while (read_next_line(data->files.fd, &line) && !is_map_line(line))
		;
	copy_map(data, data->sim.map, line);
	close(data->files.fd);
	if (is_map_valid(&data->sim, data->sim.map) == FALSE)
		return (-1);
	return (0);
}
