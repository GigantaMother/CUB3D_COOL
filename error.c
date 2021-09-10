#include "cub3d.h"

static void	error_1_10(int e);
static void	error_11_20(int e);
static void	error_21_30(int e);
static void	error_31_40(int e);

int	error(int e)
{
	ft_putstr_fd("Error\n", 2);
	if (e >= 1 && e <= 10)
		error_1_10(e);
	else if (e >= 11 && e <= 20)
		error_11_20(e);
	else if (e >= 21 && e <= 30)
		error_21_30(e);
	else if (e >= 31 && e <= 40)
		error_31_40(e);
	else
		ft_putstr_fd("Invalid error code\n", 2);
	exit (0);
}

static void	error_1_10(int e)
{
	if (e == 1)
		ft_putstr_fd("Invalid number of function arguments\n", 2);
	else if (e == 2)
		ft_putstr_fd("The file name is too short\n", 2);
	else if (e == 3)
		ft_putstr_fd("The file format is incorrect\n", 2);
	else if (e == 4)
		ft_putstr_fd("The file didn't open, what a pity\n", 2);
	else if (e == 5)
		ft_putstr_fd("The specifier string is too short\n", 2);
	else if (e == 6)
		ft_putstr_fd("No specifiers in file\n", 2);
	else if (e == 7)
		ft_putstr_fd("Specifier R.x not a digit\n", 2);
	else if (e == 8)
		ft_putstr_fd("There is no space after the R.x specifier\n", 2);
	else if (e == 9)
		ft_putstr_fd("Specifier R.y is not a digit\n", 2);
	else if (e == 10)
		ft_putstr_fd("Duplicate specifier\n", 2);
}

static void	error_11_20(int e)
{
	if (e == 11)
		ft_putstr_fd("The R.x specifier is too large \
re-initialization of color\n", 2);
	else if (e == 12)
		ft_putstr_fd("The R.x specifier is too large \
re-initialization of color\n", 2);
	else if (e == 13)
		ft_putstr_fd("R.x specifier too small / not specified\n", 2);
	else if (e == 14)
		ft_putstr_fd("The specifier R.y is too small / not specified\n", 2);
	else if (e == 15)
		ft_putstr_fd("Invalid specifier\n", 2);
	else if (e == 16)
		ft_putstr_fd("The meaning of the color is spelled incorrectly\n", 2);
	else if (e == 17)
		ft_putstr_fd("Color values cannot be such a large number / \
re-initialization of color\n", 2);
	else if (e == 18)
		ft_putstr_fd("Color is incomplete\n", 2);
	else if (e == 19)
		ft_putstr_fd("There should be no comma after the last color parameter\n", 2);
	else if (e == 20)
		ft_putstr_fd("Incorrect print mode was transferred during printing\n", 2);
}

static void	error_21_30(int e)
{
	if (e == 21)
		ft_putstr_fd("Players more than 1\n", 2);
	else if (e == 22)
		ft_putstr_fd("Forbidden symbol in the map\n", 2);
	else if (e == 23)
		ft_putstr_fd("Too many lines in the map\n", 2);
	else if (e == 24)
		ft_putstr_fd("Too many columns in the map\n", 2);
	else if (e == 25)
		ft_putstr_fd("No player on the map\n", 2);
	else if (e == 26)
		ft_putstr_fd("The map is split\n", 2);
	else if (e == 27)
		ft_putstr_fd("There was not enough memory for the required number of lines\n", 2);
	else if (e == 28)
		ft_putstr_fd("There was not enough memory for one of the lines\n", 2);
	else if (e == 29)
		ft_putstr_fd("The map is too small\n", 2);
	else if (e == 30)
		ft_putstr_fd("Items on the map cannot be positioned like this\n", 2);
}

static void	error_31_40(int e)
{
	if (e == 31)
		ft_putstr_fd("Failed to initialize mlx\n", 2);
	else if (e == 32)
		ft_putstr_fd("After permission, extra characters\n", 2);
	else if (e == 33)
		ft_putstr_fd("There can be no spaces in color initialization\n", 2);
	else if (e == 34)
		ft_putstr_fd("Extra characters at the end of color initialization\n", 2);
	else if (e == 35)
		ft_putstr_fd("At the end of the initialization of the texture, \
extra characters\n", 2);
	else if (e == 36)
		ft_putstr_fd("malloc error\n", 2);
	else if (e == 37)
		ft_putstr_fd("mlx_xpm_file_to_image error\n", 2);
	else if (e == 38)
		ft_putstr_fd("mlx_new_image error\n", 2);
	else if (e == 39)
		ft_putstr_fd("\n", 2);
	else if (e == 40)
		ft_putstr_fd("\n", 2);
}
