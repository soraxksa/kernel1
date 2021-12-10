#include "string.h"


uint32_t strlen(const char *str)
{
    uint32_t size = 0;
    while(str[size])
        size++;
    return size;
}

void append(char *str, char c)
{
    uint32_t len = strlen(str);
    str[len] = c;
    str[len+1] = 0x00;
}


//tmp
static int32_t min(uint32_t a, uint32_t b)
{
    return (a > b) ? b : a;
}

int32_t strcmp(const char *str1, const char *str2)
{
    uint32_t len1 = strlen(str1), len2 = strlen(str2);
    uint32_t len = min(len1, len2);
    uint32_t cnt = 0;
    while(str1[cnt] - str2[cnt] == 0 && cnt < len)
        cnt++;
    if(str1[cnt] - str2[cnt] == 0)
        return 0;
    else
        return str1[cnt] - str2[cnt];

    
}




