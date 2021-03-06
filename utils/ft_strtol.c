/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtol.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gianlucapirro <gianlucapirro@student.42      +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/20 11:10:07 by gpirro        #+#    #+#                 */
/*   Updated: 2022/04/07 12:32:50 by gpirro        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdbool.h>

bool	ft_strtol(const char *s, long int *store)
{
	unsigned long int	nr;

	nr = 0;
	while ((*s >= '\t' && *s <= '\r') || *s == ' ' )
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			return (false);
		s++;
	}
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (false);
		nr = (nr * 10) + (*s - '0');
		s++;
	}
	*store = nr;
	return (true);
}
