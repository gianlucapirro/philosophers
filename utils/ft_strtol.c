/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 11:10:07 by gpirro            #+#    #+#             */
/*   Updated: 2022/04/06 17:54:41 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>

long int	ft_strtol(const char *s)
{
	unsigned long int	nr;
	int					neg;

	nr = 0;
	neg = 1;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ' )
		s++;
	if (*s == '-')
		neg = -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		if ((nr * 10 + (*s - '0')) < nr)
		{
			if (neg > 0)
				return (-1);
			return (0);
		}
		nr = nr * 10;
		nr = nr + (long int)(*s - '0');
		s++;
	}
	return (nr * neg);
}
