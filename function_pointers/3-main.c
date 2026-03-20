#include <stdio.h>
#include <stdlib.h>
#include "3-calc.h"

/**
 * main - performs simple operations
 * @argc: number of arguments
 * @argv: array of arguments
 *
 * Return: 0
 */
int main(int argc, char *argv[])
{
    int a, b;
    int (*op)(int, int);

    if (argc != 4)
    {
        printf("Error\n");
        exit(98);
    }

    op = get_op_func(argv[2]);
    if (op == NULL)
    {
        printf("Error\n");
        exit(99);
    }

    a = atoi(argv[1]);
    b = atoi(argv[3]);

    if ((argv[2][0] == '/' || argv[2][0] == '%') && b == 0)
    {
        printf("Error\n");
        exit(100);
    }

    printf("%d\n", op(a, b));
    return (0);
}