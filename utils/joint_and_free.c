/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joint_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:15:39 by pmaimait          #+#    #+#             */
/*   Updated: 2022/11/29 14:16:42 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../pipex.h"
#include"../pipex_bonus.h"

char	*joint_and_free(char *str, char *buf)
{
	char	*to_free;

	to_free = ft_strjoin(str, buf);
	free(str);
	return (to_free);
}
