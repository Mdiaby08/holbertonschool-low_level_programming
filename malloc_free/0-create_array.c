#include "main.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * create_array - creates an array of chars
 * @size: size of the array
 * @c: char to initialize the array with
 *
 * Return: pointer to the array, or NULL if it fails
 */
char *create_array(unsigned int size, char c)
{
char *p;
unsigned int i;
if (size == 0)
return (NULL);
p = malloc(size * sizeof(char));
if (p == NULL)
return (NULL);
for (i = 0; i < size; i++)
p[i] = c;
return (p);
}
