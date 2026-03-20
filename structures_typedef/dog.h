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

/* New type dog_t as alias for struct dog */
typedef struct dog dog_t;

/* Prototypes */
void init_dog(struct dog *d, char *name, float age, char *owner);
void print_dog(struct dog *d);

#endif /* DOG_H */