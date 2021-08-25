/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_argument.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/08/24 12:49:12 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/24 16:28:37 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include "../libft/libft.h"

void	check_argument(t_port *port, int ac, char *cub_file)
{
	int	check;

	if (ac != 2)
		ft_error(WRONG_ARGC, port);
	check = ft_strcmp(cub_file + ft_strlen(cub_file) - 4, ".cub");
	if (ft_strcmp(cub_file + ft_strlen(cub_file) - 4, ".cub"))
		ft_error(NO_CUB_EXT, port);
}
