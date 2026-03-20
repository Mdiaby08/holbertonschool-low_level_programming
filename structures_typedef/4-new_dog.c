#include <stdlib.h>
#include "dog.h"

/**
*_strlen - returns the length of a string
*@s: string to evaluate
*
*Return: the length of the string
*/
int _strlen(char *s)
{
int i = 0;
while (s[i] != '\0')
i++;
return (i);
}

/**
*_strcpy - copies a string to a buffer
*@dest: destination buffer
*@src: source string
*
*Return: pointer to dest
*/
char *_strcpy(char *dest, char *src)
{
int i = 0;
while (src[i] != '\0')
{
dest[i] = src[i];
i++;
}
dest[i] = '\0';
return (dest);
}

/**
*new_dog - creates a new dog
*@name: dog's name
*@age: dog's age
*@owner: dog's owner
*
*Return: pointer to new dog_t, or NULL if failure
*/
dog_t *new_dog(char *name, float age, char *owner)
{
dog_t *d;
int len1, len2;
if (name == NULL || owner == NULL)
return (NULL);
d = malloc(sizeof(dog_t));
if (d == NULL)
return (NULL);
len1 = _strlen(name);
len2 = _strlen(owner);
d->name = malloc(sizeof(char) * (len1 + 1));
if (d->name == NULL)
{
free(d);
return (NULL);
}
d->owner = malloc(sizeof(char) * (len2 + 1));
if (d->owner == NULL)
{
free(d->name);
free(d);
return (NULL);
}
_strcpy(d->name, name);
_strcpy(d->owner, owner);
d->age = age;
return (d);
}
