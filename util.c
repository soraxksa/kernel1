
#include "util.h"

void memcpy(char *src, char *dest, uint32_t n)
{
    for(uint32_t i = 0; i < n; i++)
    {
        *(dest+i) = *(src+i); 
    }
}
