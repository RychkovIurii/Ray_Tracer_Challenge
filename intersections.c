/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 12:42:12 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/10 19:12:39 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

t_list	*ft_lstnew(void *content)
{
	t_list	*ptr;

	ptr = (t_list *)malloc(sizeof(t_list));
	if (!ptr)
		return (NULL);
	ptr->content = content;
	ptr->next = NULL;
	return (ptr);
}

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*ptr;

	ptr = lst;
	while (ptr != NULL && ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst == NULL || new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

void	ft_lstclear_safe(t_list **lst)
{
	t_list	*ptr;
	t_list	*tmp;

	if (lst)
	{
		ptr = *lst;
		while (ptr != NULL)
		{
			tmp = ptr->next;
			free(ptr);
			ptr = tmp;
		}
		*lst = NULL;
	}
}

void	ft_lstremove(t_list **lst, void *content)
{
	t_list	*ptr;
	t_list	*prev;

	if (lst == NULL || *lst == NULL)
		return ;
	ptr = *lst;
	prev = NULL;
	while (ptr != NULL)
	{
		if (ptr->content == content)
		{
			if (prev == NULL)
				*lst = ptr->next;
			else
				prev->next = ptr->next;
			free(ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n > 0)
	{
		*temp = 0;
		n--;
		temp++;
	}
}

t_intersection prepare_computations(t_intersection hit, t_ray ray, t_intersects *xs)
{
	t_intersection comps;
	t_list *containers = NULL;
	t_list *temp;
	int i;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = get_ray_position(ray, comps.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.over_point = add_tuple(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.normalv);
	comps.inside = 0;

	for (i = 0; i < xs->count; i++)
	{
		if (xs->array[i].t == hit.t)
		{
			if (containers == NULL)
				comps.n1 = 1.0;
			else
			{
				t_shape *shape = (t_shape *)ft_lstlast(containers)->content;
				comps.n1 = shape->material.refractive_index;
			}
		}

		temp = containers;
		while (temp)
		{
			if (temp->content == xs->array[i].object)
			{
				ft_lstremove(&containers, temp->content);
				break;
			}
			temp = temp->next;
		}
		if (!temp)
			ft_lstadd_back(&containers, ft_lstnew(xs->array[i].object));

		if (xs->array[i].object == hit.object)
		{
			if (containers == NULL)
				comps.n2 = 1.0;
			else
			{
				t_shape *shape = (t_shape *)ft_lstlast(containers)->content;
				comps.n2 = shape->material.refractive_index;
			}
			break;
		}
	}

	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = negate_tuple(comps.normalv);
	}
	ft_lstclear_safe(&containers);

	return (comps);
}

/* t_intersection prepare_computations(t_intersection hit, t_ray ray, t_intersects *xs)
{
	t_intersection comps;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = get_ray_position(ray, comps.t);
	comps.eyev = negate_tuple(ray.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.over_point = add_tuple(comps.point, multiply_tuple_scalar(comps.normalv, EPSILON));
	comps.reflectv = reflect(ray.direction, comps.normalv);
	if (dot(comps.normalv, comps.eyev) < 0)
	{
		comps.inside = 1;
		comps.normalv = negate_tuple(comps.normalv);
	}
	else
		comps.inside = 0;
	return (comps);
}
 */