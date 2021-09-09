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
	// printf("%d %d %c \n", (int)row, (int)col, map->field[(int)row] [(int)col]);
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

void calculate_img1(t_print_data *vel, t_map *map, int x)
{
	vel->cameraX = 2 * x / (double)map->lodev.w - 1;
	vel->rayDirX = map->lodev.dirX + map->lodev.planeX * vel->cameraX;
	vel->rayDirY = map->lodev.dirY + map->lodev.planeY * vel->cameraX;
	vel->mapX = (int)(map->lodev.posX);
	vel->mapY = (int)(map->lodev.posY);
	vel->deltaDistX = fabs(1 / vel->rayDirX);
	vel->deltaDistY = fabs(1 / vel->rayDirY);
	vel->hit = 0;
}

void calculate_img2(t_print_data *vel, t_map *map)
{
	if (vel->rayDirX < 0)
	{
		vel->stepX = -1;
		vel->sideDistX = (map->lodev.posX - vel->mapX) * vel->deltaDistX;
	}
	else
	{
		vel->stepX = 1;
		vel->sideDistX = (vel->mapX + 1.0 - map->lodev.posX) * vel->deltaDistX;
	}
	if (vel->rayDirY < 0)
	{
		vel->stepY = -1;
		vel->sideDistY = (map->lodev.posY - vel->mapY) * vel->deltaDistY;
	}
	else
	{
		vel->stepY = 1;
		vel->sideDistY = (vel->mapY + 1.0 - map->lodev.posY) * vel->deltaDistY;
	}
}

void calculate_img3(t_print_data *vel, t_map *map)
{
	while(vel->hit == 0)
	{
		if(vel->sideDistX < vel->sideDistY)
		{
			vel->sideDistX += vel->deltaDistX;
			vel->mapX += vel->stepX;
			vel->side = 0;
		}
		else
		{
			vel->sideDistY += vel->sideDistY;
			vel->mapY += vel->stepY;
			vel->side = 1;
		}
		if(map->field[vel->mapX][vel->mapY] == '1')
			vel->hit = 1;
	}
}

void calculate_img4(t_print_data *vel, t_map *map)
{
	if (vel->side == 0)
		vel->perpWallDist = (vel->mapX - map->lodev.posX + (1 - vel->stepX) / 2) / vel->rayDirX;
	else
		vel->perpWallDist = (vel->mapY - map->lodev.posY + (1 - vel->stepY) / 2) / vel->rayDirY;
	vel->lineHeight = (int)(map->lodev.h / vel->perpWallDist);
	vel->drawStart = -(vel->lineHeight) / 2 + map->lodev.h / 2;
	if (vel->drawStart < 0)
		vel->drawStart = 0;
	vel->drawEnd = vel->lineHeight / 2 + map->lodev.h / 2;
	if (vel->drawEnd >= map->lodev.h)
		vel->drawEnd = map->lodev.h - 1;
	if (vel->side == 0)
		vel->wallX = map->lodev.posY + vel->perpWallDist * vel->rayDirY;
	else
		vel->wallX = map->lodev.posX + vel->perpWallDist * vel->rayDirX;
}

void calculate_img5(t_print_data *vel, t_map *map)
{
	int num;

	num = numOfText(vel->side, vel->stepY, vel->stepX);
	vel->texX = (int)(vel->wallX * (double)(map->text[num].sprites_width));
	if (vel->side == 0 && vel->rayDirX > 0)
		vel->texX = map->text[num].sprites_width - vel->texX - 1;
	if (vel->side == 1 && vel->rayDirY < 0)
		vel->texX = map->text[num].sprites_width - vel->texX - 1;
	vel->numText = num;
	vel->step = 1.0 * map->text[num].sprites_height / vel->lineHeight;
	vel->texPos = (vel->drawStart - map->lodev.h / 2 + vel->lineHeight / 2) * vel->step;
}

void display_game(t_print_data *vel, t_map *map, int x)
{
	int	w;

	w = 0;
		//printf("%d - x| %d | %f %f | %f | %f | %f\n", x,vel->numText,vel->texPos,vel->step,vel->perpWallDist,vel->rayDirX,vel->rayDirY );
	while(w < map->spec.r.y)
	{
		if (w >= vel->drawStart && w <= vel->drawEnd)
		{
			int texY = (int)vel->texPos & (map->text[vel->numText].sprites_height - 1);
			vel->texPos += vel->step;
			my_mlx_pixel_put(&map->grap, x, w, map->text[vel->numText].data[texY * 
			map->text[vel->numText].sprites_height + vel->texX]);
		}
		else if (w < vel->drawStart)
			my_mlx_pixel_put(&map->grap, x, w, map->c);
		else if (w > vel->drawEnd)
			my_mlx_pixel_put(&map->grap, x, w, map->f);
		w++;
	}
}

int	ft_map_print(t_map *map)
{
	t_print_data velues;


	for(int x = 0; x < map->lodev.w; x++)
    {
		calculate_img1(&velues, map, x);
		calculate_img2(&velues, map);
		calculate_img3(&velues, map);
		calculate_img4(&velues, map);
		calculate_img5(&velues, map);
		display_game(&velues, map, x);

		
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
		{
			perpWallDist = (mapX -  map->lodev.posX + (1 - stepX) / 2) / rayDirX;
			// printf("%f\n", perpWallDist);
		}
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
		// TO DO/ make it fot array of textures
		int numText = numOfText(side, stepY, stepX);
		int texX = (int)(wallX * (double)(map->text[numText].sprites_width));
		if(side == 0 && rayDirX > 0)
			texX = map->text[numText].sprites_width - texX - 1;
		if(side == 1 && rayDirY < 0)
			texX = map->text[numText].sprites_width - texX - 1;
		
		double step = 1.0 *  map->text[0].sprites_height / lineHeight;
		double texPos = (drawStart -  map->lodev.h / 2 + lineHeight / 2) * step;		
		// int numText = 0;
		//printf("%d - x| %d | %f %f | %f | %f | %f\n", x, numText, texPos, step, perpWallDist, rayDirX, rayDirY );
		for (int w = 0; w < map->spec.r.y; w++)
		{
			if (w >= drawStart && w <= drawEnd)
			{
				int texY = (int)texPos & (map->text[numText].sprites_height - 1);
				texPos += step;
				my_mlx_pixel_put(&map->grap, x, w, map->text[numText].data[texY * 
				map->text[numText].sprites_height + texX]);
			}
			else if (w < drawStart)
				my_mlx_pixel_put(&map->grap, x, w, map->c);
			else if (w > drawEnd)
				my_mlx_pixel_put(&map->grap, x, w, map->f);
		}
		
		//printf("Kek\n");
	}
	// printf("map->lodev.dirX= %f ", map->lodev.dirX);
	// printf("map->lodev.dirY= %f\n", map->lodev.dirY);
	// printf("map->lodev.planeX= %f ", map->lodev.planeX);
	// printf("map->lodev.planeY= %f\n", map->lodev.planeY);
	ft_mini_map(map);
	mlx_put_image_to_window(map->grap.mlx, map->grap.win, map->grap.img, 0, 0);
	return (0);
}

int key_hook_mouse(int x, int y, t_map *map)
{
	int x_t;
	int y_t;

	x_t = 0;
	y_t = 0;

	// mlx_mouse_get_pos(map->grap.win, &x_t, &y_t);
	// if (x_t > map->spec.r.x/2)
	// {
	// 	write(1, "R\n", 2);
	// 	key_hook_press_turn_r(map);
	// 	ft_map_print(map);
	// }
	// else if (x_t < map->spec.r.x/2)
	// {
	// 	write(1, "L\n", 2);
	// 	key_hook_press_turn_l(map);
	// 	ft_map_print(map);
	// }
	// mlx_mouse_move(map->grap.win, map->spec.r.x/2, map->spec.r.y/2);

	//printf("Hello");
	//write(1, "Hello\n", 6);
	//printf("x= %d y= %d\n", x, y);
	return (1);
}

int	main_graphics(t_map *map)
{
	if (init_grap(map) == 0)
		return (0);
	init_text(map);
	init_mini_map(map);
	ft_map_print(map);
	//---
	mlx_mouse_show();
	mlx_mouse_move(map->grap.win, map->spec.r.x/2, map->spec.r.y/2);
	//----
	mlx_hook(map->grap.win, 2, 0, key_hook_press, map);
	mlx_hook(map->grap.win, 3, 0, key_hook_repress, map); 
	mlx_hook(map->grap.win, 17, 0, key_hook_close, map);
	//mlx_hook(map->grap.win, 6, 0, key_hook_mouse, map);
	mlx_loop(map->grap.mlx);
	return (1);
}
