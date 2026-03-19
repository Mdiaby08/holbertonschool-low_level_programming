#include "main.h"
#include <stdlib.h>

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 *           containing a copy of the string given as a parameter
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string, or NULL if it fails
 */
char *_strdup(char *str)
{
char *p;
unsigned int len = 0;
unsigned int i;
if (str == NULL)
return (NULL);
while (str[len] != '\0')
len++;
p = malloc((len + 1) * sizeof(char));
if (p == NULL)
return (NULL);
for (i = 0; i < len; i++)
p[i] = str[i];
p[len] = '\0';
return (p);
}
