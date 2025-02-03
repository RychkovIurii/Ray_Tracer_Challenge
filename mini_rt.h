/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:50:25 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/03 16:07:49 by irychkov         ###   ########.fr       */
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

t_light		point_light(t_tuple position, t_tuple intensity);
t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess);
t_tuple		lighting(t_material material, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv);
t_tuple		normal_at(t_sphere sphere, t_tuple world_point);
t_intersection prepare_computations(t_intersection hit, t_ray ray);

#endif