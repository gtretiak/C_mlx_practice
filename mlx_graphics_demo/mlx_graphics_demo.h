/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_graphics_demo.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:47:45 by gtretiak          #+#    #+#             */
/*   Updated: 2025/06/14 18:48:13 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_GRAPHICS_DEMO_H
# define MLX_GRAPHICS_DEMO_H

typedef struct	s_img
{
	void	*img;
	char	*pixels;
	int	bits_per_pixel;
	int	endian;
	int	line_len;
} t_img;

typedef struct	s_mlx_data
{
	void	*mlx;
	void	*window;
	int	color;
	t_img	img;
} t_mlx_data;

#endif
