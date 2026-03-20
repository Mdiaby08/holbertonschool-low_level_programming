#include "main.h"
#include <stdlib.h>

/**
 * array_range - creates an array of integers
 * @min: first value of the array
 * @max: last value of the array
 *
 * Return: pointer to the newly created array,
 *         or NULL if min > max or malloc fails
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
