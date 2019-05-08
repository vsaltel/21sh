/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjointf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frossiny <frossiny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:35:17 by frossiny          #+#    #+#             */
/*   Updated: 2019/05/07 15:04:29 by vsaltel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjointf(char const *s1, char const *s2, char const *s3)
{
	char	*dst;

	if (!s1 || !s2 || !s3 ||
			!(dst = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3))))
		return (NULL);
	ft_strcpy(dst, s1);
	ft_strcat(dst, s2);
	free((char *)s1);
	free((char *)s2);
	ft_strcat(dst, s3);
	free((char *)s3);
	return (dst);
}
