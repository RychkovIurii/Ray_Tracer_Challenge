/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 15:24:46 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 14:36:27 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CANVAS_H
# define CANVAS_H

# include "mini_rt.h"

typedef struct	s_canvas
{
	int			width;
	int			height;
	t_tuple		**pixels;
}				t_canvas;

t_canvas	*create_canvas(int width, int height);
void		write_pixel(t_canvas *canvas, int x, int y, t_tuple color);
t_tuple		pixel_at(t_canvas *canvas, int x, int y);
t_canvas	*canvas_to_ppm(t_canvas *canvas, char *filename);
void		free_canvas(t_canvas *canvas);

#endif
