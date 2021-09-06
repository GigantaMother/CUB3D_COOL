#include "cub3d.h"

static void	error_1_10(int e);
static void	error_11_20(int e);
static void	error_21_30(int e);
static void	error_31_40(int e);

// Основаная функция для выхова ошибок
// остальные для их перечисления
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
		printf("Неверный код ошибки\n");
	exit (0);
}

static void	error_1_10(int e)
{
	if (e == 1)
		printf("Неверное кол-во аргументов функции\n");
	else if (e == 2)
		printf("Имя файла слишком короткое\n");
	else if (e == 3)
		printf("Формат файлa неверен\n");
	else if (e == 4)
		printf("Файл не открылся, какая жалость\n");
	else if (e == 5)
		printf("Cтрока спецификатора слишком короткая\n");
	else if (e == 6)
		printf("Нет спецификаторов в файле\n");
	else if (e == 7)
		printf("Cпецификатора R.x не цифра\n");
	else if (e == 8)
		printf("После спецификатора R.x нет пробела\n");
	else if (e == 9)
		printf("Cпецификатора R.y не цифра\n");
	else if (e == 10)
		printf("Дублирующийся спецификатор\n");
}

static void	error_11_20(int e)
{
	if (e == 11)
		printf("Cпецификатора R.x слишком большой\n");
	else if (e == 12)
		printf("Cпецификатора R.y слишком большой\n");
	else if (e == 13)
		printf("Cпецификатора R.x слишком маленький/не задан\n");
	else if (e == 14)
		printf("Cпецификатора R.y слишком маленький/не задан\n");
	else if (e == 15)
		printf("Неверный спецификатор\n");
	else if (e == 16)
		printf("Значение цвета напиcано неправильно\n");
	else if (e == 17)
		printf("Значения цвета не может быть такой большой цифрой/\
		повторная инициализация цвета\n");
	else if (e == 18)
		printf("Цвет задан неполностью\n");
	else if (e == 19)
		printf("После последнего параметра цвета не должно быть запятой\n");
	else if (e == 20)
		printf("При распечатке был передан неправильно режим печати\n");
}

static void	error_21_30(int e)
{
	if (e == 21)
		printf("Игроков больше 1\n");
	else if (e == 22)
		printf("Запрещённый символ в карте\n");
	else if (e == 23)
		printf("Строк в карте слишком много\n");
	else if (e == 24)
		printf("Столбцов в карте слишком много\n");
	else if (e == 25)
		printf("Нет игрока на карте\n");
	else if (e == 26)
		printf("Карта разделена\n");
	else if (e == 27)
		printf("Не хватило памяти под нужное кол-во строк\n");
	else if (e == 28)
		printf("Не хватило памяти под одну из строк\n");
	else if (e == 29)
		printf("Карта слишком маленькая\n");
	else if (e == 30)
		printf("Предметы на карте не могут так располагаться\n");
}

static void	error_31_40(int e)
{
	if (e == 31)
		printf("Не удалось иницилизирвоать mlx\n");
	else if (e == 32)
		printf("После разрешения лишнии символы\n");
	else if (e == 33)
		printf("В инициализации цвета не может быть пробелов\n");
	else if (e == 34)
		printf("В конце инициализации цвета лишнии символы\n");
	else if (e == 35)
		printf("В конце инициализации текстуры лишнии символы\n");
	else if (e == 36)
		printf("\n");
	else if (e == 37)
		printf("\n");
	else if (e == 38)
		printf("\n");
	else if (e == 39)
		printf("\n");
	else if (e == 40)
		printf("\n");
}
