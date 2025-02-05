/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: irychkov <irychkov@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:58:58 by irychkov          #+#    #+#             */
/*   Updated: 2025/02/05 14:59:20 by irychkov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void print_matrix(t_matrix m)
{
	for (int i = 0; i < m.size; i++)
	{
		for (int j = 0; j < m.size; j++)
			printf("%f ", m.matrix[i][j]);
		printf("\n");
	}
}
