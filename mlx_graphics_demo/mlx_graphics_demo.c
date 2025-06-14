/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_graphics_demo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtretiak <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 18:47:21 by gtretiak          #+#    #+#             */
/*   Updated: 2025/06/14 18:47:38 by gtretiak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include "X11/X.h"
#include "mlx_graphics_demo.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 1024
#define HEIGHT 768
#include <time.h>
#include <unistd.h>

void	my_pixel_put(t_img *img, int x, int y, int color);
int	ft_waiting(t_mlx_data *data);
int	ft_handler(int keysym, t_mlx_data *data);
int	ft_button(int button, int x, int y, t_mlx_data *data);
int	encode_rgb(unsigned char red, unsigned char green, unsigned char blue);
int	ft_expose(t_mlx_data *data);
void	ft_draw(t_mlx_data *data);
void	ft_fill(t_mlx_data *data, int color);
void	ft_offset(t_mlx_data *data);

int	main(void)
{
	t_mlx_data	data;
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.window = mlx_new_window(data.mlx, WIDTH, HEIGHT, "My window");
	if (!data.window)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	data.img.pixels = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_len, &data.img.endian);
	printf("bits_per_pixel = %d\nline_len = %d\nendian = %d\n", data.img.bits_per_pixel, data.img.line_len, data.img.endian);
	ft_draw(&data);
	data.color = 0xff0000;
//	mlx_key_hook(data.window, ft_handler, &data);
	mlx_mouse_hook(data.window, ft_button, &data);
	mlx_hook(data.window, KeyPress, KeyPressMask, ft_handler, &data);
	mlx_loop_hook(data.mlx, ft_waiting, &data);
	mlx_expose_hook(data.window, ft_expose, &data);
	mlx_loop(data.mlx);
	mlx_destroy_display(data.mlx);
	mlx_destroy_window(data.mlx, data.window);
	free(data.mlx);
	free(data.window);
}

void	ft_draw(t_mlx_data *data)
{
	int	x;
	int	y;
	srand(time(NULL));
	x = WIDTH * 0.1;
	y = HEIGHT * 0.1;
	while (x < WIDTH * 0.9)
	{
		y = HEIGHT * 0.1;
		while (y < HEIGHT * 0.9)
		{
			mlx_pixel_put(data->mlx, data->window, x, y, rand() % 0x00ff00);
			y++;
		}
		x++;
	}
	mlx_string_put(data->mlx, data->window, WIDTH * 0.5, HEIGHT * 0.95, 0xffffff, "My Pollock");
}

void	ft_fill(t_mlx_data *data, int color)
{
	int	x;
	int	y;
	x = WIDTH * 0.1;
	y = HEIGHT * 0.1;
	while (x < WIDTH * 0.9)
	{
		y = HEIGHT * 0.1;
		while (y < HEIGHT * 0.9)
		{
			mlx_pixel_put(data->mlx, data->window, x, y, color);
			y++;
		}
		x++;
	}
}

int	ft_expose(t_mlx_data *data)
{
	static int	x;
	x = 0;
	x++;
	printf("Expose event has been triggered for the %d time\n", x);
	ft_draw(data);
	return (0);
}

int	ft_waiting(t_mlx_data *data)
{
	mlx_string_put(data->mlx, data->window, WIDTH * 0.1, HEIGHT * 0.95, data->color, "Use your keyboard or mouse");
	if (data->color == 0xff0000)
		data->color = 0x00ff00;
	else if (data->color == 0x00ff00)
		data->color = 0x0000ff;
	else if (data->color == 0x0000ff)
		data->color = 0xffffff;
	else
		data->color = 0xff0000;
//	sleep(1);
	return (0);
}

int	ft_handler(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape || keysym == XK_q)
	{
		printf("The %d key (ESC) has been pressed\n\n", keysym);
		mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit (1);
	}
	else if (keysym == XK_r)
	{
		printf("RED!\n\n");
		ft_fill(data, encode_rgb(255, 0, 0));
	}
	else if (keysym == XK_g)
	{
		printf("GREEN!\n\n");
		ft_fill(data, encode_rgb(0, 0xff, 0));
	}
	else if (keysym == XK_b)
	{
		printf("BLUE!\n\n");
		ft_fill(data, 0xff);
	}
	else if (keysym == XK_p | keysym == XK_i)
	{
		printf("IMAGE!\n\n");
		ft_offset(data);
		mlx_put_image_to_window(data->mlx, data->window, data->img.img, 0, 0);
	}
	printf("The %d key has been pressed\n\n", keysym);
	return (0);
}

int	ft_button(int button, int x, int y, t_mlx_data *data)
{
	if (button == 1)
	{
		printf("Left mouse button has been pressed at (%d, %d)!\n", x, y);
		if (WIDTH * 0.99 <= x && HEIGHT * 0.99 >= y)
		{
			printf("The X has been clicked, so bye!");
			mlx_destroy_window(data->mlx, data->window);
			mlx_destroy_display(data->mlx);
			free(data->mlx);
			exit (1);
		}
	}
	else if (button == 3)
		printf("Right mouse button has been pressed at (%d, %d)!\n", x, y);
	else if (button == 2)
		printf("Both mouse buttons have been pressed simultaneously at (%d, %d)!\n", x, y);
	else if (button == 4)
		printf("The user scrolled the display UP at (%d, %d)!\n", x, y);
	else if (button == 5)
		printf("The user scrolled the display DOWN at (%d, %d)!\n", x, y);
	return (0);
}

int	encode_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

void	my_pixel_put(t_img *img, int x, int y, int color)
{
	int	offset;
	
	offset = (img->line_len * y) + (x * (img->bits_per_pixel / 8));
	*((unsigned int *)(offset + img->pixels)) = color;
}

void	ft_offset(t_mlx_data *data)
{
	static int	r = 0;
	static int	g = 0;
	static int	b = 0;
	for (int y = 0; y < HEIGHT; y++)
	{
		for (int x = 0; x < WIDTH; x++)
		{
			int color = (r << 16) | (g << 8) | b;
			my_pixel_put(&data->img, x, y, color);
			if (r < 255)
				r++;
			else if (r == 255 && g < 255)
			{
				r = 0;
				g++;
				r++;
			}
			else if (r == 255 && g == 255 && b < 255)
			{
				b++;
				g = 0;
				r = 0;
				g++;
			}
			else if (r == 255 && g == 255 & b == 255)
				r = g = b = 0;
		}
	}	
}
