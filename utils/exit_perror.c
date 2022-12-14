/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_perror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 18:33:37 by pmaimait          #+#    #+#             */
/*   Updated: 2022/11/11 18:37:11 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include"../pipex_bonus.h"

void	exit_perror(const char *str, int code)
{
	perror(str);
	exit(code);
}
