#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 *print_all - prints anything
 *@format: list of types of arguments
 *
 *Return: nothing
 */
void print_all(const char * const format, ...)
{
va_list args;
int i = 0;
char *str;
char *sep = "";
va_start(args, format);
while (format && format[i])
{
if (format[i] == 'c' || format[i] == 'i' ||
format[i] == 'f' || format[i] == 's')
{
printf("%s", sep);
if (format[i] == 'c')
printf("%c", va_arg(args, int));
if (format[i] == 'i')
printf("%d", va_arg(args, int));
if (format[i] == 'f')
printf("%f", (double)va_arg(args, double));
if (format[i] == 's')
{
str = va_arg(args, char *);
if (str == NULL)
str = "(nil)";
printf("%s", str);
}
sep = ", ";
}
i++;
}
printf("\n");
va_end(args);
}
