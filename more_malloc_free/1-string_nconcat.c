#include "main.h"
#include <stdlib.h>

/**
 * string_nconcat - concatenates two strings
 * @s1: first string
 * @s2: second string
 * @n: number of bytes of s2 to concatenate
 *
 * Return: pointer to newly allocated memory containing s1 + n bytes of s2,
 *         or NULL if allocation fails
 */
char *string_nconcat(char *s1, char *s2, unsigned int n)
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
if (n >= len2)
n = len2;
p = malloc((len1 + n + 1) * sizeof(char));
if (p == NULL)
return (NULL);
for (i = 0; i < len1; i++)
p[i] = s1[i];
for (j = 0; j < n; j++)
p[i + j] = s2[j];
p[len1 + n] = '\0';
return (p);
}
