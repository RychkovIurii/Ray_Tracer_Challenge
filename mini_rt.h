/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:50:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/04 16:38:03 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "structs.h"
# include "tuple.h"
# include "matrix.h"
# include "rays.h"
# include "canvas.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

void			ft_bzero(void *s, size_t n);
t_light			point_light(t_tuple position, t_tuple intensity);
t_material		material(t_tuple color, double ambient, double diffuse, double specular, double shininess);
t_tuple			lighting(t_material material, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv);
t_tuple			normal_at(t_sphere sphere, t_tuple world_point);
t_intersection	prepare_computations(t_intersection hit, t_ray ray);
t_matrix4x4 	*view_transform(t_tuple from, t_tuple to, t_tuple up);
void			set_identity_matrix(t_matrix4x4 *result, int size);
t_world			default_world();
void			bubble_sort_intersections(t_intersection *array, int count);
t_intersects	intersect_world(t_world world, t_ray ray);
t_tuple			color_at(t_world world, t_ray ray);
t_camera		*create_camera(int hsize, int vsize, double field_of_view);
t_ray			ray_for_pixel(t_camera *camera, int px, int py);
t_canvas		*render(t_camera *camera, t_world world);


#endif
