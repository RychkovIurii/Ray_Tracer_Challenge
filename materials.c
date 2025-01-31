/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:13:58 by irychkov          #+#    #+#             */
/*   Updated: 2025/01/31 15:48:10 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Function to create a material.
** @param color: The color of the material.
** @param ambient: The ambient light of the material.
** @param diffuse: The diffuse light of the material.
** @param specular: The specular light of the material.
** @param shininess: The shininess of the material.
** @return The struct of the material.
*/
t_material	material(t_tuple color, double ambient, double diffuse, double specular, double shininess)
{
	t_material material;

	material.color = color;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	return (material);
}

t_tuple	lighting(t_material material, t_light light, t_tuple position, t_tuple eyeview, t_tuple normalv)
{
	t_tuple effective_color;
	t_tuple lightv;
	t_tuple reflectv;
	t_tuple ambient;
	double reflect_dot_eye;
	double light_dot_normal;
	t_tuple diffuse;
	t_tuple specular;
	double factor;

	effective_color = multiply_color(material.color, light.intensity);
	lightv = normalize(substract_tuple(light.position, position));
	ambient = multiply_tuple_scalar(effective_color, material.ambient);
	light_dot_normal = dot(lightv, normalv);
	if (light_dot_normal < 0)
	{
		diffuse = create_color(0, 0, 0);
		specular = create_color(0, 0, 0);
	}
	else
	{
		diffuse = multiply_tuple_scalar (effective_color, (material.diffuse * light_dot_normal));
		reflectv = reflect(negate_tuple(lightv), normalv);
		reflect_dot_eye = dot(reflectv, eyeview);
		if (reflect_dot_eye <= 0)
			specular = create_color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, material.shininess);
			specular = multiply_tuple_scalar(light.intensity, material.specular * factor);
		}
	}
	return (add_tuple(add_tuple(ambient, diffuse), specular));
}

t_material	default_material()
{
	t_tuple color = create_tuple(1, 1, 1, 0);
	return (material(color, 0.1, 0.9, 0.9, 200.0));
}


t_matrix identity_matrix(int size)
{
	t_matrix id = create_matrix(size);
	for (int i = 0; i < size; i++)
		id.matrix[i][i] = 1;
	return id;
}

/* 
t_tuple	normal_at(t_sphere sphere, t_tuple world_point);
t_light		point_light(t_tuple position, t_tuple intensity);

int main()
{
	t_canvas	*canvas;
	t_tuple		black;
	t_ray		ray;		// Ray from the eye to the wall
	t_tuple		wall_position;	// Position on the wall
	double		world_x;
	double		world_y;

	int canvas_pixels = 1000;
	double wall_z = 10.0;
	double wall_size = 7.0;
	double half = wall_size / 2;
	double pixel_size = wall_size / canvas_pixels;

	t_tuple sphere_color = create_tuple(1, 0.2, 1, 0);
	t_material sphere_material = material(sphere_color, 0.1, 0.9, 0.9, 200.0);
	t_tuple light_position = create_tuple(-10, 10, -10, 1);
	t_tuple light_color = create_tuple(1, 1, 1, 0);
	t_light light = {light_position, light_color};

	// Ray origin
	t_tuple ray_origin = point(0, 0, -5);

	// Create the sphere
	t_sphere sphere = {point(0, 0, 0), 1, identity_matrix(4), sphere_material};

	// Create the canvas
	canvas = create_canvas(canvas_pixels, canvas_pixels);

	// Create the color
	black = create_color(0, 0, 0); // black

	// Set the sphere's transform
	//set_transform(&sphere, scaling_matrix(1, 0.5, 1)); // round1.ppm
	//set_transform(&sphere, scaling_matrix(0.5, 1, 1)); // round2.ppm
	//set_transform(&sphere, multiply_matrices (rotation_z_matrix(M_PI / 4), scaling_matrix(0.5, 1, 1))); // round3.ppm
	//set_transform(&sphere, multiply_matrices(shearing_matrix(1, 0, 0, 0, 0, 0), scaling_matrix(0.5, 1, 1))); // round4.ppm


	// Cast rays
	for (int y = 0; y < canvas_pixels; y++)
	{
		world_y = half - pixel_size * y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			world_x = -half + pixel_size * x;
			wall_position = point(world_x, world_y, wall_z);
			ray = create_ray(ray_origin, normalize(substract_tuple(wall_position, ray_origin)));
			ray.direction = normalize(ray.direction);

			// Check for intersection
			t_intersects xs = intersect_sphere(sphere, ray);
			t_intersection *hit_intersection = hit(xs);

			if (hit_intersection != NULL)
			{
				t_tuple point = get_ray_position(ray, hit_intersection->t);
				t_tuple normal = normal_at(sphere, point);
				t_tuple eye = negate_tuple(ray.direction);
				t_tuple color = lighting(sphere.material, light, point, eye, normal);
				write_pixel(canvas, x, y, color);
			}
			else
			{
				// If miss, color the pixel black
				write_pixel(canvas, x, y, black);
			}

			if (xs.array != NULL)
				free(xs.array);
		}
	}
	canvas_to_ppm(canvas, "blue.ppm");
	free_canvas(canvas);
	free_matrix(sphere.transform);
	return (0);
}
 */

