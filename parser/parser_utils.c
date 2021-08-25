/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/23 11:34:36 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/25 13:07:46 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	cubfile_read_is_complete(t_maze *blueprint, char *mapfile)
{
	int	pos;

	pos = blueprint->filepos;
	while (mapfile[pos] == ' ' || mapfile[pos] == '\n')
		pos++;
	if (mapfile[pos] == 'R' || mapfile[pos] == 'S')
		return (0);
	else if (blueprint->north_texture && blueprint->south_texture
		&& blueprint->east_texture && blueprint->west_texture
		&& blueprint->ceiling_color != -1
		&& blueprint->floor_color != -1)
		return (1);
	else
		return (0);
}
