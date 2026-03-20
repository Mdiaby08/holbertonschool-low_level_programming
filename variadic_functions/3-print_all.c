#include "variadic_functions.h"
#include <stdarg.h>
#include <stdio.h>

/**
 * print_all - prints anything
 * @format: list of types of arguments
 *
 * Return: nothing
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

            switch (format[i])
            {
                case 'c':
                    printf("%c", va_arg(args, int));
                    break;
                case 'i':
                    printf("%d", va_arg(args, int));
                    break;
                case 'f':
                    printf("%f", (double)va_arg(args, double));
                    break;
                case 's':
                    str = va_arg(args, char *);
                    if (!str)
                        str = "(nil)";
                    printf("%s", str);
                    break;
            }

            sep = ", ";
        }
        i++;
    }

    printf("\n");
    va_end(args);
}
