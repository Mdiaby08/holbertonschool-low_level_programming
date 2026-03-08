#include "main.h"

/**
 * _strncpy - copies a string
 * @dest: destination buffer
 * @src: source string
 * @n: number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_strncpy(char *dest, char *src, int n)
{
int i = 0;

/* Copy characters from src */
while (i < n && src[i] != '\0')
{
dest[i] = src[i];
i++;
}

/* If src is shorter than n, pad with '\0' */
while (i < n)
{
dest[i] = '\0';
i++;
}

return (dest);
}
