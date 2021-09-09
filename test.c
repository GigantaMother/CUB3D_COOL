// #include <stdlib.h>
// #include <stdio.h>
// #include <unistd.h>

// typedef struct test
// {
// 	char	*a;
// 	int		i;
// } S;

// void ft_test_2(char **a);

// void ft_test(char **a, S *test)
// {
// 	(*a) = malloc(sizeof(char) * 4);
// 	(*a)[0] = 'L';
// 	(*a)[1] = 'O';
// 	(*a)[2] = 'P';
// 	(*a)[3] = '\0';

// 	test->i++;

// 	ft_test_2(&test->a);

// 	printf("a(test)= %s\n", test->a);

// 	// (test->a) = malloc (sizeof(char) * 4);

// 	// (test->a)[0] = 'L';
// 	// (test->a)[1] = 'O';
// 	// (test->a)[2] = 'P';
// 	// (test->a)[3] = '\0';

// }

// void ft_test_2(char **a)
// {
// 	(*a) = malloc(sizeof(char) * 4);
// 	(*a)[0] = 'L';
// 	(*a)[1] = 'O';
// 	(*a)[2] = 'P';
// 	(*a)[3] = '\0';
// }

// int main()
// {
// 	char	**a;
// 	S		test;
// 	test.i = 5;

// 	ft_test(a, &test);

// 	printf("a(main)= %s\n", *a);
// 	printf("i(main)= %d\n", test.i);
// 	printf("T.a(main)= %s\n", test.a);

// 	return (0);
// }