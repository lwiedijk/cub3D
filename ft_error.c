/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:30:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/07/22 13:21:33 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "cub3d.h"

void	ft_error(int error_code)
{
	if (error_code == INCORRECT_CUB_FILE)
		write(1, "Error\n!not a valid cub-file!\n", 29);
	if (error_code == MALLOC_FAIL)
		write(1, "Error\n!malloc fail!\n", 20);
	if (error_code == INVALID_FD)
		write(1, "Error\n!invalid fd!\n", 19);
	if (error_code == READ_FAIL)
		write(1, "Error\n!read failed!\n", 20);
	if (error_code == WRONG_ARGC)
		write(1, "Error\n!wrong amound of arguments!\n", 34);
	if (error_code == INVALID_MAP)
		write(1, "Error\n!invalid map!\n", 20);
	if (error_code == 8)
		write(1, "FFFFFFFF\n", 9);
	write(1, "Exiting program, please reboot...\n", 34);
	exit(1);
}
