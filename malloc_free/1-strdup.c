#include "main.h"
#include <stdlib.h>
#include <string.h>

/**
*_strdup - copy a string of character
*@str: dtring of character
*
*Return: string of char, or NULL if it fails
*/

char *_strdup(char *str)
{
char *p;
unsigned int len;
unsigned int i;
if (str == NULL)
return (NULL);
len = strlen(str);
p = malloc((len + 1) * sizeof(char));
if (p == NULL)
return (NULL);
for (i = 0; i <= len; i++)
p[i] = str[i];
return (p);
}
