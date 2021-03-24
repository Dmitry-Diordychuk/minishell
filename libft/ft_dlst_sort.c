/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlst_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdustin <kdustin@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 10:22:07 by kdustin           #+#    #+#             */
/*   Updated: 2021/02/14 11:55:32 by kdustin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		swap(void **d1, void **d2)
{
	void *temp;

	temp = *d1;
	*d1 = *d2;
	*d2 = temp;
}

static t_dlist	*main_loop(t_dlist *pivot, t_dlist *left, t_dlist *right,
														t_dcompfunc comp)
{
	int right_freeze;

	right_freeze = 0;
	while (1)
	{
		while (comp(left->content, pivot->content) < 0 && left->next != NULL &&
													left->next->sorted != TRUE)
		{
			if (left == right)
				right_freeze = 1;
			left = left->next;
		}
		while (comp(right->content, pivot->content) >= 0 && right != left &&
															right_freeze == 0)
			right = right->prev;
		if (left == pivot)
			return (pivot);
		else if (left == right)
		{
			swap(&(left->content), &(pivot->content));
			return (left);
		}
		swap(&(left->content), &(right->content));
	}
}

static void		run_sort(t_dlist *start, t_dcompfunc comp, char *direction)
{
	t_dlist	*pivot;
	t_dlist	*left;
	t_dlist	*right;
	t_dlist *next;

	if (start == NULL || start->sorted == TRUE)
		return ;
	pivot = start;
	left = start;
	if (!ft_strcmp("left", direction))
		while (left->prev != NULL && left->prev->sorted != TRUE)
			left = left->prev;
	else
		while (pivot->next != NULL && pivot->next->sorted != TRUE)
			pivot = pivot->next;
	right = pivot->prev;
	if (right == NULL || right->sorted == TRUE)
	{
		pivot->sorted = TRUE;
		return ;
	}
	next = main_loop(pivot, left, right, comp);
	next->sorted = TRUE;
	run_sort(next->prev, comp, "left");
	run_sort(next->next, comp, "right");
}

void			ft_dlst_sort(t_dlist **list, t_dcompfunc comp)
{
	t_dlist *temp;

	if (list != NULL && *list != NULL)
	{
		temp = *list;
		run_sort(temp, comp, "right");
		while (temp->prev != NULL)
			temp = temp->prev;
		*list = temp;
		while (temp != NULL)
		{
			temp->sorted = FALSE;
			temp = temp->next;
		}
	}
}
