/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:23:59 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/29 13:35:09 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* This function creates a canvas with the given width and height. */

t_canvas	*create_canvas(int width, int height)
{
	t_canvas	*canvas;
	int			i;
	int			j;

	canvas = (t_canvas *)malloc(sizeof(t_canvas));
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = (t_tuple **)malloc(sizeof(t_tuple *) * height);
	i = 0;
	while (i < height)
	{
		canvas->pixels[i] = (t_tuple *)malloc(sizeof(t_tuple) * width);
		j = 0;
		while (j < width)
		{
			canvas->pixels[i][j] = create_color(0, 0, 0);
			j++;
		}
		i++;
	}
	return (canvas);
}

/* This function writes a color to the pixel at the given coordinates. */

void write_pixel(t_canvas *canvas, int x, int y, t_tuple color)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		canvas->pixels[y][x] = color;
	}
}

/* This function returns the color of the pixel at the given coordinates. */

t_tuple	pixel_at(t_canvas *canvas, int x, int y)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
	{
		return (canvas->pixels[y][x]);
	}
	return (create_color(0, 0, 0)); // Return black if out of bounds
}

/* This function clamps a value to a given range. */

int	round_value(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

/* This function writes a color to a file in PPM format. */

int	write_color(FILE *file, t_tuple color)
{
	int r = round_value((int)(color.x * 255), 0, 255);
	int g = round_value((int)(color.y * 255), 0, 255);
	int b = round_value((int)(color.z * 255), 0, 255);
	return (fprintf(file, "%d %d %d", r, g, b));
}

/* This function writes the canvas to a file in PPM format. */

t_canvas *canvas_to_ppm(t_canvas *canvas, char *filename)
{
	FILE		*file;
	int			i;
	int			j;
	t_tuple		color;
	int			line_length;
	
	line_length = 0;
	file = fopen(filename, "w");
	fprintf(file, "P3\n%d %d\n255\n", canvas->width, canvas->height);
	i = 0;
	while (i < canvas->height)
	{
		j = 0;
		while (j < canvas->width)
		{
			color = pixel_at(canvas, j, i);
			// Calculate the length of the next color string
			char color_string[20];
			int color_length = snprintf(color_string, sizeof(color_string), "%d %d %d",
										round_value((int)(color.x * 255), 0, 255),
										round_value((int)(color.y * 255), 0, 255),
										round_value((int)(color.z * 255), 0, 255));

			// If adding this color exceeds 70 characters, start a new line
			if (line_length > 0 && line_length + color_length + 1 > 70)
			{
				fprintf(file, "\n");
				line_length = 0;
			}
			if (line_length > 0)
			{
				fprintf(file, " ");
				line_length++;
			}
			fprintf(file, "%s", color_string);
			line_length += color_length;
			j++;
		}
		fprintf(file, "\n");
		line_length = 0;
		i++;
	}
	fclose(file);
	return (canvas);
}