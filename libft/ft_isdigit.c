/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isdigit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <lwiedijk@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/17 15:34:44 by lwiedijk      #+#    #+#                 */
/*   Updated: 2021/02/17 15:34:47 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int argument)
{
	if (argument >= '0' && argument <= '9')
		return (1);
	return (0);
}
