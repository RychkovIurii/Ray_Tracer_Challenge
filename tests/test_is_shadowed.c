/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_shadowed.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:10:55 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 15:29:56 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <assert.h>

int main()
{
	t_world		world;
	t_tuple		p;
	int			shadowed;

	world = default_world();
	shadowed = is_shadowed(world, point(0, 10, 0));
	assert(shadowed == 0);
	shadowed = is_shadowed(world, point(10, -10, 10));
	assert(shadowed == 1);
	shadowed = is_shadowed(world, point(-20, 20, -20));
	assert(shadowed == 0);
	shadowed = is_shadowed(world, point(-2, 2, -2));
	assert(shadowed == 0);
	printf("is_shadowed: OK\n");
	return (0);
}

