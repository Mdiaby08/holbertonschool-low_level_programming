#include "main.h"

/**
 * print_last_digit - prints the last digit of a number
 * @n: the number to extract the last digit from
 *
 * Return: the last digit
 */
int print_last_digit(int n)
{
int digit = n % 10;

if (digit < 0)
digit = -digit;

_putchar('0' + digit);

return (digit);
}