
#include "lib.h"

int ef_strcmp(const char *str1, const char *str2)
{
    int i;

    for (i = 0; str1[i] && str2[i] && str1[i] == str2[i]; i++) {};
    return ((unsigned char) str1[i] - (unsigned char) str2[i]);
}

long ef_extract_number(const char *str)
{
    long total;

    if (str == NULL)
        return (-1);
    total = 0;
    while (*str && (*str == '\n' || *str == '\t' || *str == ' '))
        str++;
    if (*str == '-' || *str == '+')
        str++;
    
    for (int i = 0; str[i]; i++)
    {
        total *= 10;
        if (total == 0 && !(str[i] >= '0' && str[i] <= '9'))
            return (-1);
        total += str[i] - '0';
    }
    return (total);
}

long ef_strlen(char *str)
{
    long size;
    
    size = 0;
    for (; str[size];size++) {};
    return (size);
}