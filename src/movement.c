/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 09:31:23 by kseligma          #+#    #+#             */
/*   Updated: 2024/08/11 21:14:15 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
	Detecs if the space to move is clear.
	The 50th state of a door is an open door.
*/
static bool	is_space(int value)
{
	if (value == '0' || value == DOOR_NS + 50 || value == DOOR_WE + 50)
		return (true);
	return (false);
}

/*
	If the place to move is inside the collision, returns the distance
	to the wall. Otherwise returns the movement itself.

	'return (wall_dist * 0.9999 - wall_offset);'. Getting too
	close to the wall could result in rounding errors,
	glitching the player inside and causing bounces.
*/
static float	movex(t_player *player, int **map, double movement)
{
	float	wall_offset;

	if (movement > 0)
		wall_offset = MIN_WALL_DIST;
	else
		wall_offset = -MIN_WALL_DIST;
	if (is_space(map[(int)(player->old_pos.z)] \
	[(int)(player->old_pos.x + movement + wall_offset)]) &&
	is_space(map[(int)(player->old_pos.z + wall_offset)] \
	[(int)(player->old_pos.x + movement + wall_offset)]) &&
	is_space(map[(int)(player->old_pos.z - wall_offset)] \
	[(int)(player->old_pos.x + movement + wall_offset)]))
		return (movement);
	return (0);
}

static float	movez(t_player *player, int **map, double movement)
{
	float	wall_offset;

	if (movement > 0)
		wall_offset = MIN_WALL_DIST;
	else
		wall_offset = -MIN_WALL_DIST;
	if (is_space(map[(int)(player->old_pos.z + movement + wall_offset)] \
	[(int)(player->old_pos.x)]) &&
	is_space(map[(int)(player->old_pos.z + movement + wall_offset)] \
	[(int)(player->old_pos.x + wall_offset)]) &&
	is_space(map[(int)(player->old_pos.z + movement + wall_offset)] \
	[(int)(player->old_pos.x - wall_offset)]))
		return (movement);
	return (0);
}

/*
	Old player position is stored to not give priority to any direction.
	If not, z movement will be calculated from the new x position. This
	could cause inconsistency close to walls.

	To move forwards add and backwards add the direction vector to the
	position, multiplied by MS (Or its negative).

	To move left and right, do the same but with perpendicular vectors
	the two directions will be (y, -x) and (-y, x).
*/
void	do_translation(t_player *player, int **map, unsigned int key_flag)
{
	player->old_pos.x = player->pos.x;
	player->old_pos.z = player->pos.z;
	if (key_flag & CUBK_W)
	{
		player->pos.x += movex(player, map, MS * player->dir.x);
		player->pos.z += movez(player, map, MS * player->dir.z);
	}
	else if (key_flag & CUBK_S)
	{
		player->pos.x += movex(player, map, -MS * player->dir.x);
		player->pos.z += movez(player, map, -MS * player->dir.z);
	}
	else if (key_flag & CUBK_A)
	{
		player->pos.x += movex(player, map, MS * player->dir.z);
		player->pos.z += movez(player, map, -MS * player->dir.x);
	}
	else if (key_flag & CUBK_D)
	{
		player->pos.x += movex(player, map, -MS * player->dir.z);
		player->pos.z += movez(player, map, MS * player->dir.x);
	}
}

/*
	While a key is pressed the direction vector of the player is multiplied 
	by a rotation matrix, the used angle is ROTMS,  -ROTMS.

	cos(a)	- sin(a)
	sin(a)	cos(a)
*/
void	do_rotation(t_player *player, t_ged *ged, int unsigned key_flag)
{
	double	aux;
	double	ang;

	ged->old_mouse_pos.x = ged->mouse_pos.x;
	ged->old_mouse_pos.z = ged->mouse_pos.z;
	mlx_get_mouse_pos(ged->mlx, &ged->mouse_pos.x, &ged->mouse_pos.z);
	ang = (ged->mouse_pos.x - ged->old_mouse_pos.x) * MOUSE_ROTMS_FACTOR;
	if (key_flag & CUBK_L)
	{
		aux = player->dir.x;
		player->dir.x = aux * cos(-ROTMS) - player->dir.z * sin(-ROTMS);
		player->dir.z = aux * sin(-ROTMS) + player->dir.z * cos(-ROTMS);
	}
	if (key_flag & CUBK_R)
	{
		aux = player->dir.x;
		player->dir.x = aux * cos(ROTMS) - player->dir.z * sin(ROTMS);
		player->dir.z = aux * sin(ROTMS) + player->dir.z * cos(ROTMS);
	}
	if (ang != 0)
	{
		aux = player->dir.x;
		player->dir.x = aux * cos(ang) - player->dir.z * sin(ang);
		player->dir.z = aux * sin(ang) + player->dir.z * cos(ang);
	}
}
