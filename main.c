/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:16:18 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/14 18:26:55 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuple.h"
#include "canvas.h"

int main()
{
	t_canvas	*canvas;
	t_tuple		color;
	int			i;
	int			j;

	canvas = create_canvas(1000, 2000);
	color = create_color(1, 0.8, 0.6);
	for (i = 0; i < 1000; i++)
	{
		for (j = 0; j < 2000; j++)
		{
			write_pixel(canvas, i, j, color);
		}
	}
	canvas_to_ppm(canvas, "red.ppm");
	return (0);
}
