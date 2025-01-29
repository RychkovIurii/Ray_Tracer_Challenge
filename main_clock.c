/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 12:34:27 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/17 14:14:51 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "canvas.h"
#include "matrix.h"

#define WIDTH 1000
#define HEIGHT 1000
#define RADIUS (WIDTH * 3 / 8)  // Clock's radius is 3/8 of canvas width
#define CENTER_X (WIDTH / 2)
#define CENTER_Y (HEIGHT / 2)

/* Challenge is to write a program that uses a rotation matrix to compute 
the positions of those hours on the clock face, and draw a pixel onto 
a canvas for each of them. */

int main()
{
	t_canvas	*canvas;
	t_tuple		black, white;
	t_matrix	rotation;
	t_tuple		p;
	int			i;
	int			j;

	canvas = create_canvas(WIDTH, HEIGHT);
	black = create_color(0, 0, 0);
	for (i = 0; i < WIDTH; i++)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			write_pixel(canvas, i, j, black);
		}
	}
	white = create_color(1, 1, 1);
	rotation = rotation_y_matrix(M_PI / 6);
	p = point(0, 0, 1);
	for (i = 0; i < 12; i++)
	{
		// Scale and translate to canvas coordinates
		int x = (int)(p.x * RADIUS + CENTER_X);
		int y = (int)(p.z * RADIUS + CENTER_Y);

		// Ensure the point is within canvas bounds
		if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
			write_pixel(canvas, x, y, white);
			printf("Pixel at (%d, %d)\n", x, y);
		}
		p = multiply_matrix_by_tuple(rotation, p);
		/* int x = (int)(p.x * 100 + 500);
		int y = (int)(p.z * 100 + 500);
		if (x >= 0 && x < 1000 && y >= 0 && y < 1000) {  // Boundary check
			write_pixel(canvas, x, y, white);
		} */
	}
	canvas_to_ppm(canvas, "clock.ppm");
	return (0);
}
