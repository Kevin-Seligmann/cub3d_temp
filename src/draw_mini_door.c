/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_door.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:26:41 by oseivane          #+#    #+#             */
/*   Updated: 2024/08/20 20:08:00 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	draw_mini_door_closed(t_ged *ged, unsigned int x, unsigned int y)
{
	unsigned int	square_x;
	unsigned int	square_y;

	square_x = 0;
	square_y = 0;
	while (square_x < MM_SCALE)
	{
		square_y = 0;
		while (square_y < MM_SCALE)
		{
			mlx_put_pixel(ged->minimap, x * MM_SCALE + square_x,
				y * MM_SCALE + square_y, 0xf71109FF);
			square_y++;
		}
		square_x++;
	}
}

void	draw_mini_door_opened(t_ged *ged, unsigned int x, unsigned int y)
{
	unsigned int	square_x;
	unsigned int	square_y;

	square_x = 0;
	square_y = 0;
	while (square_x < MM_SCALE)
	{
		square_y = 0;
		while (square_y < MM_SCALE)
		{
			mlx_put_pixel(ged->minimap, x * MM_SCALE + square_x,
				y * MM_SCALE + square_y, 0x08f409FF);
			square_y++;
		}
		square_x++;
	}
}

void	draw_mini_door_move(t_ged *ged, unsigned int x, unsigned int y)
{
	unsigned int	square_x;
	unsigned int	square_y;

	square_x = 0;
	square_y = 0;
	while (square_x < MM_SCALE)
	{
		square_y = 0;
		while (square_y < MM_SCALE)
		{
			mlx_put_pixel(ged->minimap, x * MM_SCALE + square_x,
				y * MM_SCALE + square_y, 0xFFFF00FF);
			square_y++;
		}
		square_x++;
	}
}

void	draw_mini_door(t_ged *ged, t_sim *sim, unsigned int x, unsigned int y, t_v2 *corner)
{
	if (sim->map[corner->z + y][corner->x + x] == 100 || sim->map[corner->z + y][corner->x + x] == 200)
		draw_mini_door_closed(ged, x, y);
	else if (sim->map[corner->z + y][corner->x + x] == 150 || sim->map[corner->z + y][corner->x + x] == 250)
		draw_mini_door_opened(ged, x, y);
	else
		draw_mini_door_move(ged, x, y);
}
