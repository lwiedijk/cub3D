/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/20 12:30:28 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/08/18 14:00:59 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "cub3d.h"

void	ft_error_continue(int error_code, t_port *port)
{
	if (error_code == NO_NUMBER)
		printf("Error\n!Two positive numbers must be entered for screensize!\n");
	if (error_code == ILLEGAL_CHAR)
		printf("Error\n!That character is not allowed at this spot!\n");
	if (error_code == BAD_NUM_RANGE)
		printf("Error\n!Plz enter A number between 0 and 255!\n");
	if (error_code == NO_COMMA)
		printf("Error\n!Color needs to be separated by comma and comma only!\n");
	if (error_code == INVALID_PATH)
		printf("Error\n!This Texture-path is not valid!\n");
	if (error_code == NO_SPRITE)
		printf("Error\n!Sprite-bonus is not implemented, plz remove from cub-file!\n");
	printf("Exiting program, please adjust input and reboot...\n");
	free_at_error(port);
	exit(1);
}

void	ft_error(int error_code, t_port *port)
{
	if (error_code == INCORRECT_CUB_FILE)
		printf("Illegal, missing or wrong order of elements!\n");
	if (error_code == MALLOC_FAIL)
		printf("Error\n!malloc fail!\n");
	if (error_code == INVALID_FD)
		printf("Error\n!invalid fd!\n");
	if (error_code == READ_FAIL)
		printf("Error\n!read failed!\n");
	if (error_code == WRONG_ARGC)
		printf("Error\n!wrong amound of arguments!\n");
	if (error_code == INVALID_MAP)
		printf("Error\n!invalid map!\n");
	if (error_code == MISSING_MAP)
		printf("Error\n!No map is provided!\n");
	if (error_code == TOO_MANY_ELEMENTS)
		printf("Error\n!Too many elements provided!\n");
	if (error_code == TOO_MANY_PLAYERS)
		printf("Error\n!Only one player is allowed in the map!\n");
	if (error_code == MISSING_PLAYER)
		printf("Error\n!No valid player in the map!\n");
	if (error_code == NOT_ALL_ELEMENTS)
		printf("Error\n!Not all necessary elements are provided!\n");
	ft_error_continue(error_code, port);
}
