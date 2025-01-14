/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:47:05 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/14 15:15:18 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"

/* The little program, firing virtual projectiles and seeing how far they go. */

/* tick(environment, projectile) function which returns a new
projectile, representing the given projectile after one unit of time has passed. */

typedef struct s_projectile
{
	t_tuple	position;
	t_tuple	velocity;
}	t_projectile;

typedef struct s_environment
{
	t_tuple	gravity;
	t_tuple	wind;
}	t_environment;

t_projectile	tick(t_environment env, t_projectile proj)
{
	t_projectile	new_proj;

	new_proj.position = add_tuple(proj.position, proj.velocity);
	new_proj.velocity = add_tuple(add_tuple(proj.velocity, env.gravity), env.wind);
	return (new_proj);
}

int	main()
{
	t_projectile	proj;
	t_environment	env;
	int ticks = 0;

	proj.position = point(0, 1, 0);
	proj.velocity = normalize(vector(1, 1, 0));
	proj.velocity = multiply_tuple_scalar(proj.velocity, 1.2);
	env.gravity = vector(0, -0.1, 0);
	env.wind = vector(-0.01, 0, 0);

	while (proj.position.y > 0)
	{
		proj = tick(env, proj);
		printf("Position: x = %f, y = %f, z = %f\n", proj.position.x, proj.position.y, proj.position.z);
		ticks++;
	}
	printf("Number of ticks: %d\n", ticks);
	return (0);
}
