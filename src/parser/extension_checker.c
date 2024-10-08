/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extension_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kseligma <kseligma@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 13:28:15 by kseligma          #+#    #+#             */
/*   Updated: 2024/08/19 14:34:21 by kseligma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "parser.h"

/*
	Checks that the string (file) ends with the extension provided.
*/
void	extension_checker(t_cube *data, char *file, char *extension)
{
	size_t	extension_length;
	size_t	file_length;

	extension_length = ft_strlen(extension);
	file_length = ft_strlen(file);
	if (extension_length > file_length)
		exit_cubed(data, -1, WRONG_EXTENSION, file);
	while (extension_length > 0)
	{
		if (extension[extension_length] != file[file_length])
			exit_cubed(data, -1, WRONG_EXTENSION, file);
		extension_length --;
		file_length --;
	}
}
