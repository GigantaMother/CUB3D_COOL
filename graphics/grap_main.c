#include "../cub3d.h"

int char_in_str(char cr, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == cr)
			return 1;
	}
	return 0;
}

int numOfText(int side, int stepY, int stepX)
{
	if (side == 1)
    {
      if (stepY == -1)
        return WE;
      else
        return EA;
    }
    else
    {
      if (stepX == -1)
        return NO;
      else
        return SO;
    }
}

int it_is_not_wall(t_map* map, double row, double col)
{
	printf("%d %d %c \n", (int)row, (int)col, map->field[(int)row] [(int)col]);
	if(map->field[(int)row] [(int)col] != '0')
		return 0;
	else if(map->field[(int)(row + 0.11)] [(int)(col + 0.11)] != '0')
		return 0;
	else if(map->field[(int)(row + 0.11)] [(int)(col)] != 48)
		return 0;
	else if(map->field[(int)(row)] [(int)(col + 0.11)] != 48)
		return 0;
	else if(map->field[(int)(row - 0.11)] [(int)(col - 0.11)] != 48)
		return 0;
	else if(map->field[(int)(row - 0.11)] [(int)(col)] != 48)
		return 0;
	else if(map->field[(int)(row)] [(int)(col - 0.11)] != 48)
		return 0;
	return (1);
}

void	change_player_position(t_map *map, double row, double col)
{
	if (it_is_not_wall(map, row, col))
	{
		map->lodev.posX = row;
		map->lodev.posY = col;
	}
	else if (it_is_not_wall(map, map->lodev.posX, col))
	{
		map->lodev.posX = row;
	}
	else if (it_is_not_wall(map, row, map->lodev.posY))
	{
		map->lodev.posY = col;
	}
}

void move_forward(t_map *map, int flag, double *x, double *y)
{
	*x += flag * map->lodev.dirX * (map->lodev.moveSpeed);
	*y += flag * map->lodev.dirY * (map->lodev.moveSpeed);	
}

void move_side(t_map *map, int flag, double *x, double *y)
{
	*y -= flag * map->lodev.dirX * (map->lodev.moveSpeed);
	*x += flag * map->lodev.dirY * (map->lodev.moveSpeed);
}

int	ft_map_print(t_map *map)
{
	for(int x = 0; x < map->lodev.w; x++)
    {
		double cameraX = 2 * x / (double)map->lodev.w - 1;
		double rayDirX = map->lodev.dirX + map->lodev.planeX * cameraX;
		double rayDirY =  map->lodev.dirY + map->lodev.planeY * cameraX;

		int mapX = (int)(map->lodev.posX);
		int mapY = (int)(map->lodev.posY);

		double sideDistX;
		double sideDistY;

		double deltaDistX = fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (map->lodev.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - map->lodev.posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (map->lodev.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - map->lodev.posY) * deltaDistY;
		}
		while (hit == 0)
		{
			if(sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if(map->field[mapX][mapY] == '1')
				hit = 1;
		}
		if(side == 0)
			perpWallDist = (mapX -  map->lodev.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY -  map->lodev.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(map->lodev.h / perpWallDist);

		int drawStart = -lineHeight / 2 + map->lodev.h / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + map->lodev.h / 2;
		if(drawEnd >= map->lodev.h)
			drawEnd = map->lodev.h - 1;
		//------------------------------------------------------------------------
		//------------------------------------------------------------------------
		double wallX;
		if (side == 0)
			wallX = map->lodev.posY + perpWallDist * rayDirY;
		else
			wallX = map->lodev.posX + perpWallDist * rayDirX;
		wallX = wallX - (int)(wallX);
		// координата x на текстуре
		//printf("WallX= %f\n", wallX);
		int texX = (int)(wallX * (double)(map->text[0].sprites_width));
		if(side == 0 && rayDirX > 0)
			texX = map->text[0].sprites_width - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = map->text[0].sprites_width - texX - 1;
		
		double step = 1.0 *  map->text[0].sprites_height / lineHeight;
		double texPos = (drawStart -  map->lodev.h / 2 + lineHeight / 2) * step;		

		//------------------------------------------------------------------------
				// while (i < map->spec.r.y)
				// {
				// 	if (i >= drawStart && i <= drawEnd)
				// 	{
				// 		my_mlx_pixel_put(&map->grap, x, i, color);
				// 	}
				// 	else if (i < drawStart)
				// 		my_mlx_pixel_put(&map->grap, x, i, Blue);
				// 	//my_mlx_pixel_put(&map->grap, x, i, color);
				// 	i++;
				// }
				//Вот так рисуется текстуру вместо цвета

	// if (side == 1)
    // {
    //   if (stepY == -1)
    //     color = 0x000000; //запад
    //   else
    //     color = 0x7FFFD4; //восток
    // }
    // else
    // {
    //   if (stepX == -1)
    //     color = 0x00008B; // север DarkBlue
    //   else
    //     color = 0x00FF00; //юг Lime
    // }
		int numText = numOfText(side, stepY, stepX);
		// int numText = 0;
		for (int w = 0; w < map->spec.r.y; w++)
		{
			if (w >= drawStart && w <= drawEnd)
			{
				int texY = (int)texPos & (map->text[numText].sprites_height - 1);
				texPos += step;
				my_mlx_pixel_put(&map->grap, x, w, map->text[numText].data[texY * map->text[numText].sprites_height + texX]);
			}
			else if (w < drawStart)
				my_mlx_pixel_put(&map->grap, x, w, map->c);
			else if (w > drawEnd)
				my_mlx_pixel_put(&map->grap, x, w, map->f);
		}
		// printf("Kek\n");
	}
	// printf("map->lodev.dirX= %f ", map->lodev.dirX);
	// printf("map->lodev.dirY= %f\n", map->lodev.dirY);
	// printf("map->lodev.planeX= %f ", map->lodev.planeX);
	// printf("map->lodev.planeY= %f\n", map->lodev.planeY);
	ft_mini_map(map);
	mlx_put_image_to_window(map->grap.mlx, map->grap.win, map->grap.img, 0, 0);
	return (0);
}

// int key_hook_mouse(int x, int y,  t_map *map)
// {

// 	return (1);
// }

int	main_graphics(t_map *map)
{
	if (init_grap(map) == 0)
		return (0);
	init_text(map);
	init_mini_map(map);
	ft_map_print(map);
	mlx_hook(map->grap.win, 2, 0, key_hook_press, map);
	mlx_hook(map->grap.win, 3, 0, key_hook_repress, map); 
	mlx_hook(map->grap.win, 17, 0, key_hook_close, map);
	//mlx_hook(map->grap.win, 6, 0, key_hook_mouse, map);
	mlx_loop(map->grap.mlx);
	return (1);
}
