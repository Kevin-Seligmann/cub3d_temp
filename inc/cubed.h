/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 16:08:39 by kseligma          #+#    #+#             */
/*   Updated: 2024/08/22 18:08:43 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H

# define CUBED_H

/* System libraries */
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>

/* User libraries/headers */
# include "libft.h"
# include "MLX42/MLX42.h"
# include "cubed_data_structures.h"
# include "defines.h"

/* Prints an error with the provided strings and returns 'return_value' */
int				print_error(int return_value, \
const char		*error_message, const char *strerror);

/* Hook for MLX that contains an actions for each key press */
void			key_hook(mlx_key_data_t keydata, void *param);

/* Performs the translation calculations */
void			do_translation(t_player *player, \
int **map, unsigned int key_flag);

/* Performs the rotation calculations */
void			do_rotation(t_player *player,
					t_ged *ged, int unsigned key_flag);

/* Stores in dst the clockwise perpendicular 2d´vector to src */
void			perp_clockwise_v2(t_v2 *src, t_v2 *dst);
void			perp_clockwise_vf2(t_vd2 *src, t_vd2 *dst);

/* Transforms RGBA into a 4 bytes hex */
unsigned int	get_rgba(int r, int g, int b, int a);

/* Draws the scene and minimap*/
void			draw_scene(t_dda *dda, t_ged *ged, t_sim *sim);
void			draw_mini_square(t_ged *ged, unsigned int x,
					unsigned int y, unsigned int colour);
void			draw_mini_map(t_ged *ged, \
t_sim *sim, t_minimap *mm);

/* Performs the raycasting algorithm, DDA */
void			ft_raycasting(t_cube *game);

/* Tests if the block hit is the side of a door */
void			check_door_side(t_dda *dda, int **map);

/* If a block is a door, tests if the door has been hit */
void			check_door_hit(t_dda *dda, \
t_player *player, int **map, int *hit);

/* DDA - Detects ray hit */
void			set_raycasting_data(t_player *player, t_dda *dda, t_ged *ged);
void			set_step(t_player *player, t_dda *dda);
void			ft_dda(t_dda *dda, t_player *player, int **map);

/* Checks if a door - open or close - has been it */
void			ft_dda_door(t_dda *dda, int **map);

/* Updates door status each frame*/
void			update_doors(t_cube *data, int **map);

/* Closes the windows to finish the simulation. */
void			escape_window(mlx_key_data_t keydata, t_cube *data);

/*On/Off the map*/
void			minimap_controls(mlx_key_data_t keydata, t_cube *data);

/* Draws sprites into the screen */
void			draw_sprites(t_cube *data);

/* Update sprites */
void			update_sprites(t_cube *data);

/* Exits the program */
void			exit_cubed(t_cube *data, int exit_code,
					char *err, const char *strerr);

/* If windows size change, update images */
void			update_size(t_cube *data, t_ged *ged);

void			sort_sprites(t_sprite_dda *spr, t_player *player);

#endif
