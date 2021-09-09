#include "../cub3d.h"

void	calculate_img1(t_print_data *vel, t_map *map, int x)
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

void	calculate_img2(t_print_data *vel, t_map *map)
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

void	calculate_img3(t_print_data *vel, t_map *map)
{
	while (vel->hit == 0)
	{
		if (vel->sideDistX < vel->sideDistY)
		{
			vel->sideDistX += vel->deltaDistX;
			vel->mapX += vel->stepX;
			vel->side = 0;
		}
		else
		{
			vel->sideDistY += vel->deltaDistY;
			vel->mapY += vel->stepY;
			vel->side = 1;
		}
		if (map->field[vel->mapX][vel->mapY] == '1')
			vel->hit = 1;
	}
}

void	calculate_img4(t_print_data *vel, t_map *map)
{
	if (vel->side == 0)
		vel->perpWallDist = (vel->mapX - map->lodev.posX
				+ (1 - vel->stepX) / 2) / vel->rayDirX;
	else
		vel->perpWallDist = (vel->mapY - map->lodev.posY
				+ (1 - vel->stepY) / 2) / vel->rayDirY;
	vel->lineHeight = (int)(map->lodev.h / vel->perpWallDist);
	vel->drawStart = -vel->lineHeight / 2 + map->lodev.h / 2;
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

void	calculate_img5(t_print_data *vel, t_map *map)
{
	vel->wallX = vel->wallX - (int)(vel->wallX);
	vel->numText = numOfText(vel->side, vel->stepY, vel->stepX);
	vel->texX = (int)(vel->wallX * (double)
			(map->text[vel->numText].sprites_width));
	if (vel->side == 0 && vel->rayDirX > 0)
		vel->texX = map->text[vel->numText].sprites_width - vel->texX - 1;
	if (vel->side == 1 && vel->rayDirY < 0)
		vel->texX = map->text[vel->numText].sprites_width - vel->texX - 1;
	vel->step = 1.0 * map->text[0].sprites_height / vel->lineHeight;
	vel->texPos = (vel->drawStart - map->lodev.h / 2 + \
	vel->lineHeight / 2) * vel->step;
}
