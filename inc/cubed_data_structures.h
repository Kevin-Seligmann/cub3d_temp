/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed_data_structures.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:33:13 by kseligma          #+#    #+#             */
/*   Updated: 2024/08/22 17:35:39 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_DATA_STRUCTURES_H

# define CUBED_DATA_STRUCTURES_H

# include "MLX42/MLX42.h"
# include "defines.h"

/* Red, green, blue, alpha (opacity) */
typedef struct s_rgba
{
	int	r;
	int	g;
	int	b;
	int	a;
}	t_rgba;

/* 2D Vector, int. */
typedef struct s_v2
{
	int	x;
	int	z;
}	t_v2;

/* 2D Vector, double. */
typedef struct s_vd2
{
	double	x;
	double	z;
}	t_vd2;

typedef struct s_sprite
{
	t_vd2	pos;
	double	dist;
	int		sprite_ind;
}	t_sprite;

typedef struct s_sprite_dda
{
	t_sprite		sprites[30];
	mlx_texture_t	*texture;
	t_vd2			pos;
	t_vd2			transform;
	double			zbuffer[MAXWIDTH];
	double			det_inv;
	t_v2			draw_start;
	t_v2			draw_end;
	t_v2			dim;
	t_v2			text;
	t_v2			ind;
	int				text_coord;
	int				screen_x;
	int				sprite_ind;
	unsigned int	color;
	int				sprite_count;
}	t_sprite_dda;

/*
	DDA variables.

	'side'. If a NS or AD wall has been hit.
	'line_'. Which section of a vertial stripe belongs to a texture.
	'wall_dist'. Distance from player to the wall it's moving.
	'texture_x'. X coordinate on texture. (0, 1).
	'camera_x'. X coordinate on camera. (-1, 1).
	'step'. Pair of -1 or 1, coordinate change based on direction.
	'pos_int'. Position on the map, floored.
	'ray_dir'. Ray direction.
	'side_dist'. Total change of position for DDA iteration.
	'delta_dist'. Change of position for DDA iteration.
	'cam_vect'. Camera vector.
	'door_hit'. A door has been hit.
	'door_side'. The side of a door has been hit.
	'door_offset'. How much the texture of the door is offset.
	'door_x'. X hit on the door axis.
	'x' - Screen X.
	'y' - Screen Y.
*/
typedef struct s_dda
{
	int				side;
	int				line_start;
	int				line_end;
	unsigned int	line_height;
	double			wall_dist;
	double			texture_x;
	double			camera_x;
	t_v2			step;
	t_v2			pos_int;
	t_vd2			ray_dir;
	t_vd2			side_dist;
	t_vd2			delta_dist;
	t_vd2			cam_vect;
	bool			door_hit;
	bool			door_side;
	double			door_offset;
	double			door_x;
	unsigned int	x;
	unsigned int	y;
	t_sprite_dda	sprite;
}	t_dda;

/*
	Player data.

	'pos'. Player position.
	'dir'. Player direction.
	'old_pos' Player position in previous iteration.
*/
typedef struct s_player
{
	t_vd2	pos;
	t_vd2	dir;
	t_vd2	old_pos;
}	t_player;

typedef struct s_minimap
{
	unsigned int	floor_color;
	unsigned int	wall_color;
	t_vd2			corner;
	t_vd2			player_center;
}	t_minimap;

/*
	Simulation data.

	'map'. Map.
	'height'. Map height.
	'width'. Map width.
	'floor_color'. Floor color.
	'ceiling_color'. Ceiling color'
	'player'. Player data.
*/
typedef struct s_sim
{
	int				**map;
	unsigned int	height;
	unsigned int	width;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	t_minimap		minimap;
	t_player		player;
}	t_sim;

/*
	Textures
*/
typedef struct s_texture_pack
{
	mlx_texture_t	*east_wall;
	mlx_texture_t	*north_wall;
	mlx_texture_t	*south_wall;
	mlx_texture_t	*west_wall;
	mlx_texture_t	*door_side;
	mlx_texture_t	*door;
	mlx_texture_t	*sprites_text[8][30];
	t_v2			sprite_ind[8];
}	t_texture_pack;

/*
	Graphic engine (MLX related) data.

	'mlx'. MLX instance.
	'img'. MLX image.
	'minimap'. MLX minimap.
	'texts'. Loaded game textures.
	'key_flag'. Which keys are being pressed.
	'mouse_pos'. Mouse offset from intial x position.
	'mouse_y'. Mouse offset from initial y position.
*/
typedef struct s_ged
{
	unsigned int	mm_scale;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_image_t		*minimap;
	t_texture_pack	textures;
	unsigned int	win_height;
	unsigned int	win_width;
	unsigned int	key_flag;
	t_v2			old_mouse_pos;
	t_v2			mouse_pos;
}	t_ged;

/*
	Parser data.

	'fd'. File descriptor.
	'config'. Configuration on a string.
	'conflig_line'. Configuration separated by lines.
	'door_found'. If a door has been found on config file.
	'sprite_found'. If a sprite has been found in the map.
*/
typedef struct s_parser
{
	int		fd;
	char	*config;
	char	**config_lines;
	bool	door_found;
	bool	sprite_found[8];
}	t_parser;

/*
	Program data. 

	'ged'. Containts data related to minilib and graphics management.
	'parse'. Contains data related to the parsir, only used for parsing.
	'sim'. Map and player data.
	'dda'. DDA Algorithm data for raycasting. 
*/
typedef struct s_cube
{
	t_parser	parse;
	t_ged		ged;
	t_sim		sim;
	t_dda		dda;
}	t_cube;

#endif
