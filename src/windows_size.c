/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   windows_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oseivane <oseivane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 13:29:43 by kseligma          #+#    #+#             */
/*   Updated: 2024/08/20 18:33:54 by oseivane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

/*
	mlx checks the new width and height are different by itself
*/
void	update_size(t_cube *data, t_ged *ged)
{
	if (ged->mlx->height > MAXHEIGHT || ged->mlx->width > MAXWIDTH)
		exit_cubed(data, -1, "Windows size too big", 0);
	mlx_resize_image(ged->img,
		ged->mlx->width, ged->mlx->height);
}
