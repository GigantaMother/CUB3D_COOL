#include "../cub3d.h"

int	ft_map_print(t_map *map)
{
	printf("Hello\n");
	
	for(int x = 0; x < map->lodev.w; x++)
    {
    	//calculate ray position and direction
      	double cameraX = 2 * x / (double)map->lodev.w - 1; //x-coordinate in camera space
      	double rayDirX = map->lodev.dirX + map->lodev.planeX * cameraX;
      	double rayDirY = map->lodev.dirY + map->lodev.planeY * cameraX;
      	//which box of the map we're in
      	int mapX = (int)(map->lodev.posX);
      	int mapY = (int)(map->lodev.posY);

		double sideDistX;
      	double sideDistY;

       	//length of ray from one x or y-side to next x or y-side
      	double deltaDistX = fabs(1 / rayDirX);
      	double deltaDistY = fabs(1 / rayDirY);
      	double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if(rayDirX < 0)
		{
			stepX = -1;
			sideDistX = ( map->lodev.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 -  map->lodev.posX) * deltaDistX;
		}
		if(rayDirY < 0)
		{
			stepY = -1;
			sideDistY = ( map->lodev.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 -  map->lodev.posY) * deltaDistY;
		}

		while (hit == 0)
      	{
       		//jump to next map square, OR in x-direction, OR in y-direction
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
        	//Check if ray has hit a wall
			if(map->field[mapX][mapY] == '1')
			{
				//printf("hint error %d \n", x);	
				hit = 1;
			}
      	}
     	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if(side == 0)
			perpWallDist = (mapX - map->lodev.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - map->lodev.posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)( map->lodev.h / perpWallDist);

      	//calculate lowest and highest pixel to fill in current stripe
    	int drawStart = -lineHeight / 2 +  map->lodev.h / 2;
			// printf("lineHeight  %d\n", map->lodev.posY );
    	if(drawStart < 0)
		{
			drawStart = 0;
		}
    	int drawEnd = lineHeight / 2 + map->lodev.h / 2;
    	if(drawEnd >=  map->lodev.h)
			drawEnd =  map->lodev.h - 1;
		
		//---*-
		// printf("x= %d\n", x);

		printf ("drawStart=%d ", drawStart);
		printf ("drawEnd=%d \n", drawEnd);

		verLine(map, x, drawStart, drawEnd, Gray);

		//void	square_print(t_map *map, t_coord start, t_coord size, int color);



		//---
	}
	mlx_put_image_to_window(map->grap.mlx, map->grap.win, map->grap.img, 0, 0);

	return (0);
}

//123 left 124 right 
//126 вверх 125 вниз 
int	key_hook_press(int keycode, t_map *map)
{
	mlx_destroy_image(map->grap.mlx, map->grap.img);
	map->grap.img = mlx_new_image(map->grap.mlx, map->spec.r.x, map->spec.r.y);
	map->grap.addr = mlx_get_data_addr(map->grap.img, &map->grap.bits_per_pixel, &map->grap.line_length,
								&map->grap.endian); 

	float x_step = cos(map->player.angle) * map->player.speed_moving;
	float y_step = sin(map->player.angle) * map->player.speed_moving;

	if (keycode == Esc )
	{
		printf("Выход через esc\n");
		mlx_destroy_window(map->grap.mlx, map->grap.win);
		exit (0);
	}
	else if (keycode == Up && map->button.up == 0)
	{
		map->button.up = 1;
		//printf("Вверх нажато\n");
	}
	else if (keycode == Down && map->button.down == 0)
	{
		map->button.down = 1;
		//printf("Вниз нажато\n");
	}
	else if (keycode == Right && map->button.right == 0)
	{
		map->button.right = 1;
		//printf("Вправо нажато\n");
	}
	else if (keycode == Left && map->button.left == 0)
	{
		map->button.left = 1;
		//printf("Влево нажато\n");
	}
	else if (keycode == Turn_right && map->button.turn_right == 0)
	{
		map->button.turn_right = 1;
		//printf("Поворот вправо нажато\n");
	}
	else if (keycode == Turn_left && map->button.turn_left == 0)
	{
		map->button.turn_left = 1;
		//printf("Поворот влево нажато\n");
	}
	else if (keycode == M)
	{
		if (map->player.cell_zoom < 4)
			map->player.cell_zoom++;
		else
			map->player.cell_zoom = 0;
		//printf("Режим миникарты\n");
	}
	else
		printf("Неизвестная клавиша %d\n", keycode);

	// движение вперёд/назад
	if (map->button.up == 1 && map->button.down == 0)
	{
		// printf("--------------------\n");
		// printf("x(до)=%f y(до)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент до(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);

		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x + x_step)] != '1')
			map->player.coord.x += x_step;
		if (map->field[(int)(map->player.coord.y + y_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y += y_step;

		// printf("x(после)=%f y(после)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент после(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);
	}
	else if (map->button.down == 1 && map->button.up == 0)
	{
		// printf("--------------------\n");
		// printf("x(до)=%f y(до)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент до(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);

		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x - x_step)] != '1')
			map->player.coord.x -= x_step;
		if (map->field[(int)(map->player.coord.y - y_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y -= y_step;

		// printf("x(после)=%f y(после)=%f\n", map->player.coord.x, map->player.coord.y);
		// printf("элемент после(%c)\n", map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x)]);
	}
	// движение вправо/влево
	if (map->button.right == 1 && map->button.left == 0)
	{
		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x - y_step)] != '1')
			map->player.coord.x -= y_step;
		if (map->field[(int)(map->player.coord.y + x_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y += x_step;
	}
	else if (map->button.left == 1 && map->button.right == 0)
	{
		if (map->field[(int)(map->player.coord.y)][(int)(map->player.coord.x + y_step)] != '1')
			map->player.coord.x += y_step;
		if (map->field[(int)(map->player.coord.y - x_step)][(int)(map->player.coord.x)] != '1')
			map->player.coord.y -= x_step;
	}
	// поворот вправо/влево
	if (map->button.turn_right == 1 && map->button.turn_left == 0)
	{
		map->player.angle += map->player.speed_turn;
	}
	else if (map->button.turn_left == 1 && map->button.turn_right == 0)
	{
		map->player.angle -= map->player.speed_turn;
	}

	printf("(%f,%f)\n", map->player.coord.x, map->player.coord.y);
	//-Менять-----------
	//map_print(map); // старая
	//------------------
	return (1);
}

int	key_hook_repress(int keycode, t_map *map)
{
	if (keycode == Up && map->button.up == 1)
	{
		map->button.up = 0;
		//printf("Вверх отжато\n");
	}
	else if (keycode == Down && map->button.down == 1)
	{
		map->button.down = 0;
		//printf("Вниз отжато\n");
	}
	else if (keycode == Right && map->button.right == 1)
	{
		map->button.right = 0;
		//printf("Вправо отжато\n");
	}
	else if (keycode == Left && map->button.left == 1)
	{
		map->button.left = 0;
		//printf("Влево отжато\n");
	}
	else if (keycode == Turn_right && map->button.turn_right == 1)
	{
		map->button.turn_right = 0;
		//printf("Поворот вправо отжато\n");
	}
	else if (keycode == Turn_left && map->button.turn_left == 1)
	{
		map->button.turn_left = 0;
		//printf("Поворот влево отжато\n");
	}

	return (1);
}

int key_hook_close(int keycode, t_map *map)
{
	printf("Выход через крестик\n");
	//mlx_destroy_window(map->grap.mlx, map->grap.win);
	exit (0);
}

int		main_graphics(t_map *map)
{
	if (init_grap(map) == 0)
		return (0);

	//-Менять-----------
	//map_print(map); // старая версия 
	//------------------
	//--------Лодев----
	map->lodev.posX = 3;
	map->lodev.posY = 8;
	map->lodev.dirX = -1.0;
	map->lodev.dirY = 0.66;
	map->lodev.w = map->spec.r.x;
	map->lodev.h = map->spec.r.y;
	map->lodev.planeX = 0;
	map->lodev.planeY = 0.66;

	ft_map_print(map);

	//-----------

	mlx_hook(map->grap.win, 2, 1L << 2, key_hook_press, map);
	mlx_hook(map->grap.win, 3, 1L << 3, key_hook_repress, map); 
	mlx_hook(map->grap.win, 17, 1L << 2, key_hook_close, map);

	mlx_loop(map->grap.mlx);
	return (1);
}
