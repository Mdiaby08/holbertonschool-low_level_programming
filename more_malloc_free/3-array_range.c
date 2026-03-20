#include "main.h"
#include <stdlib.h>

/**
 * array_range - creates an array of integers
 * @min: minimum value
 * @max: maximum value
 *
 * Return: pointer to the array, or NULL on failure
 */
int *array_range(int min, int max)
{
int *a;
int i, size;
if (min > max)
return (NULL);
size = max - min + 1;
a = malloc(size * sizeof(int));
if (a == NULL)
return (NULL);
for (i = 0; i < size; i++)
a[i] = min + i;
return (a);
}
