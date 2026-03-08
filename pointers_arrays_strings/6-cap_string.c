#include "main.h"

/**
 * cap_string - capitalizes all words of a string
 * @str: the string to modify
 *
 * Return: pointer to str
 */
char *cap_string(char *str)
{
int i = 0;
int j;
char sep[] = " \t\n,;.!?\"(){}";

while (str[i] != '\0')
{
/* Capitalize first character if it's a letter */
if (i == 0 && str[i] >= 'a' && str[i] <= 'z')
str[i] -= 32;

/* Check if previous char is a separator */
for (j = 0; sep[j] != '\0'; j++)
{
if (str[i] == sep[j] && str[i + 1] >= 'a' && str[i + 1] <= 'z')
{
str[i + 1] -= 32;
break;
}
}

i++;
}

return (str);
}
