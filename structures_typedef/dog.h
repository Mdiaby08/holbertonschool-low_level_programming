#ifndef DOG_H
#define DOG_H

/**
 * struct dog - structure describing a dog
 * @name: dog's name
 * @age: dog's age
 * @owner: dog's owner
 */
struct dog
{
    char *name;
    float age;
    char *owner;
};

/* Prototypes */
void print_dog(struct dog *d);
dog_t *new_dog(char *name, float age, char *owner);
void free_dog(dog_t *d);
void init_dog(struct dog *d, char *name, float age, char *owner);
#endif /* DOG_H */