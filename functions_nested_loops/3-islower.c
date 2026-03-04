#include "main.h"

/**
* _islower - checks for lowercase character
*
*Returns: 1 lowercase, 0 otherwise 
*/

int _islower(int c)
{
if(c >= 'a' && 'z'<= c)
return (1);
else
return (0);
}
