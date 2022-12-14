/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmaimait <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:34:30 by pmaimait          #+#    #+#             */
/*   Updated: 2022/11/14 16:35:18 by pmaimait         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"
#include"../pipex_bonus.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i])
			str[j++] = s1[i++];
	}
	i = 0;
	if (s2)
	{
		while (s2[i])
			str[j++] = s2[i++];
	}
	str[j] = '\0';
	return (str);
}
