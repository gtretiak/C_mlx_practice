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

typedef struct	s_img // here pixels are stored before being shown in a window
{
	void	*img; // a pointer to the image object created by MiniLibX
	char	*pixels; // a pointer to the raw pixel data of the image
	int	bits_per_pixel; // Usually 32 for RGBA (8 bits per channel (color))
	int	endian; // important for color byte order
	int	line_len; // number of bytes per row of pixels (may be more than image width due to padding)
} t_img;

typedef struct	s_mlx_data
{
	void	*mlx; // a pointer to the MLX connection
	void	*window; // a pointer to the created window 
	int	color; // currently selected color
	t_img	img; // embedded image structure
} t_mlx_data;

#endif
