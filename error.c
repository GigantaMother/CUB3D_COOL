#include "cub3d.h"

static void	error_1_10(int e);
static void	error_11_20(int e);
static void	error_21_30(int e);
static void	error_31_40(int e);

int	error(int e)
{
	printf("Error\n");
	if (e >= 1 && e <= 10)
		error_1_10(e);
	else if (e >= 11 && e <= 20)
		error_11_20(e);
	else if (e >= 21 && e <= 30)
		error_21_30(e);
	else if (e >= 31 && e <= 40)
		error_31_40(e);
	else
		printf("Invalid error code\n");
	exit (0);
}

static void	error_1_10(int e)
{
	if (e == 1)
		printf("Invalid number of function arguments\n");
	else if (e == 2)
		printf("The file name is too short\n");
	else if (e == 3)
		printf("The file format is incorrect\n");
	else if (e == 4)
		printf("The file didn't open, what a pity\n");
	else if (e == 5)
		printf("The specifier string is too short\n");
	else if (e == 6)
		printf("No specifiers in file\n");
	else if (e == 7)
		printf("Specifier R.x not a digit\n");
	else if (e == 8)
		printf("There is no space after the R.x specifier\n");
	else if (e == 9)
		printf("Specifier R.y is not a digit\n");
	else if (e == 10)
		printf("Duplicate specifier\n");
}

static void	error_11_20(int e)
{
	if (e == 11)
		printf("The R.x specifier is too large \
re-initialization of color\n");
	else if (e == 12)
		printf("The R.x specifier is too large \
re-initialization of color\n");
	else if (e == 13)
		printf("R.x specifier too small / not specified\n");
	else if (e == 14)
		printf("The specifier R.y is too small / not specified\n");
	else if (e == 15)
		printf("Invalid specifier\n");
	else if (e == 16)
		printf("The meaning of the color is spelled incorrectly\n");
	else if (e == 17)
		printf("Color values cannot be such a large number / \
re-initialization of color\n");
	else if (e == 18)
		printf("Color is incomplete\n");
	else if (e == 19)
		printf("There should be no comma after the last color parameter\n");
	else if (e == 20)
		printf("Incorrect print mode was transferred during printing\n");
}

static void	error_21_30(int e)
{
	if (e == 21)
		printf("Players more than 1\n");
	else if (e == 22)
		printf("Forbidden symbol in the map\n");
	else if (e == 23)
		printf("Too many lines in the map\n");
	else if (e == 24)
		printf("Too many columns in the map\n");
	else if (e == 25)
		printf("No player on the map\n");
	else if (e == 26)
		printf("The map is split\n");
	else if (e == 27)
		printf("There was not enough memory for the required number of lines\n");
	else if (e == 28)
		printf("There was not enough memory for one of the lines\n");
	else if (e == 29)
		printf("The map is too small\n");
	else if (e == 30)
		printf("Items on the map cannot be positioned like this\n");
}

static void	error_31_40(int e)
{
	if (e == 31)
		printf("Failed to initialize mlx\n");
	else if (e == 32)
		printf("After permission, extra characters\n");
	else if (e == 33)
		printf("There can be no spaces in color initialization\n");
	else if (e == 34)
		printf("Extra characters at the end of color initialization\n");
	else if (e == 35)
		printf("At the end of the initialization of the texture, \
extra characters\n");
	else if (e == 36)
		printf("malloc error\n");
	else if (e == 37)
		printf("mlx_xpm_file_to_image error\n");
	else if (e == 38)
		printf("mlx_new_image error\n");
	else if (e == 39)
		printf("\n");
	else if (e == 40)
		printf("\n");
}
