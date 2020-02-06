/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbonnete <lbonnete@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 12:52:53 by lbonnete          #+#    #+#             */
/*   Updated: 2018/11/20 14:28:36 by lbonnete         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *temp;
	t_list *res;

	if (!(lst))
		return (0);
	res = 0;
	temp = f(lst);
	if (!(new = ft_lstnew(temp->content, temp->content_size)))
		return (0);
	res = new;
	lst = lst->next;
	while (lst)
	{
		temp = f(lst);
		if (!(new->next = ft_lstnew(temp->content, temp->content_size)))
			return (0);
		new = new->next;
		lst = lst->next;
	}
	return (res);
}
