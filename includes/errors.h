/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gianlucapirro <gianlucapirro@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:57:51 by gianlucapir       #+#    #+#             */
/*   Updated: 2022/05/13 13:58:15 by gianlucapir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

typedef enum e_error {
	SUCCES,
	WRONG_AMOUNT_OF_ARGUMENTS,
	INT_OVERFLOW,
	MALLOC_FAILED,
	MUTEX_FAILED,
	PHILOSOPHER_FAIL
}	t_error;

int	p_error(char *msg, int errorcode);
int	error(int argc, char *argv[]);

#endif