/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkao <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/06 17:06:30 by fkao              #+#    #+#             */
/*   Updated: 2017/03/06 17:56:29 by fkao             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	list = malloc(sizeof(*list));
	if (list)
	{
		if (!content)
		{
			list->content_size = 0;
			list->content = NULL;
		}
		else
		{
			list->content_size = content_size;
			list->content = ft_memalloc(content_size);
			if (!list->content)
				return (NULL);
			ft_memmove(list->content, content, content_size);
		}
		list->next = NULL;
	}
	return (list);
}
