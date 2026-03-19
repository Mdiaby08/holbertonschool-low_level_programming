#include "main.h"
#include <stdlib.h>

/**
*str-concat - Write a function that concatenates two strings
*
*Return: pointer to a the contents of s1, followed by the contents of s2, and null terminated
*/
char *str_concat(char *s1, char *s2)
{
char *p;
unsigned int len1 = 0, len2 = 0, i, j;
if (s1 == NULL)
s1 = "";
if (s2 == NULL)
s2 = "";
while (s1[len1] != '\0')
len1++;
while (s2[len2] != '\0')
len2++;
p = malloc((len1 + len2 + 1) * sizeof(char));
if (p == NULL)
return (NULL);
for (i = 0; i < len1; i++)
p[i] = s1[i];
for (j = 0; j < len2; j++)
p[i + j] = s2[j];
p[len1 + len2] = '\0';
return (p);
}
