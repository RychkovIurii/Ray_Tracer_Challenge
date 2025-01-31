/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:13:34 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/14 19:35:58 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "canvas.h"

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

int main()
{
	t_projectile	proj;
	t_environment	env;
	t_canvas	*canvas;
	t_tuple		color;
	int			i;
	int			j;

	proj.position = point(0, 1, 0);
	proj.velocity = normalize(vector(1, 1.8, 0));
	proj.velocity = multiply_tuple_scalar(proj.velocity, 11.25);
	env.gravity = vector(0, -0.1, 0);
	env.wind = vector(-0.01, 0, 0);

	canvas = create_canvas(900, 550);
	color = create_color(0, 0, 0);
	for (i = 0; i < 900; i++)
	{
		for (j = 0; j < 550; j++)
		{
			write_pixel(canvas, i, j, color);
		}
	}
	while (proj.position.y > 0)
	{
		int x = (int)proj.position.x;
        int y = (int)(550 - proj.position.y); // Convert to canvas coordinates (y-axis flipped)
        t_tuple trajectory_color = create_color(1, 0, 0);
        if (x >= 0 && x < 900 && y >= 0 && y < 550) { // Check canvas bounds
            write_pixel(canvas, x, y, trajectory_color);
        }
		proj = tick(env, proj);
	}
	canvas_to_ppm(canvas, "red1.ppm");
	return (0);
}
