/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_screenres.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 15:34:09 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/07 12:14:40 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

void	put_screenres(t_maze *blueprint, char *screenres_char, char axis)
{
	int	screenres;

	screenres = ft_atoi(screenres_char);
	printf("screenres = %d\n", screenres);
	if (axis == 'x')
		blueprint->screenres_x = screenres;
	else if (axis == 'y')
		blueprint->screenres_y = screenres;
	free(screenres_char);
}

void	calc_screenres(t_maze *blueprint, char *mapfile, char axis)
{
	int		len;
	int		i;
	char	*screenres_char;
	char	*temp;

	len = 0;
	i = blueprint->filepos;
	while (ft_isdigit(mapfile[i]))
	{
		len++;
		i++;
	}
	screenres_char = (char *)malloc(sizeof(char) * (len + 1));
	if (!screenres_char)
		ft_error(MALLOC_FAIL);
	temp = &mapfile[blueprint->filepos];
	ft_strlcpy(screenres_char, temp, len + 1);
	blueprint->filepos += len;
	put_screenres(blueprint, screenres_char, axis);
}

void	parse_screenres(t_maze *blueprint, char *mapfile)
{
	blueprint->filepos++;
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	if (mapfile[blueprint->filepos] < '1' || mapfile[blueprint->filepos] > '9')
		ft_error(INCORRECT_CUB_FILE);
	calc_screenres(blueprint, mapfile, 'x');
	if (mapfile[blueprint->filepos] != ' ')
		ft_error(INCORRECT_CUB_FILE);
	while (mapfile[blueprint->filepos] == ' ')
		blueprint->filepos++;
	if (mapfile[blueprint->filepos] < '1' || mapfile[blueprint->filepos] > '9')
		ft_error(INCORRECT_CUB_FILE);
	calc_screenres(blueprint, mapfile, 'y');
	while (mapfile[blueprint->filepos] == ' '
		&& mapfile[blueprint->filepos] != '\n')
		blueprint->filepos++;
}
