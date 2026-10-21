
#include "mls.h"

int ef_contains(const char *str1, char str2)
{
    int i;
    for (i = 0; str1[i] && str1[i] != str2; i++){};
    return (str1[i] == str2 ? 1 : 0);
}

int ef_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ef_concat(char *str1, char *str2)
{
    char *returned;
    int len_str1;
    int len_str2;

    len_str1 = ef_strlen(str1);
    len_str2 = ef_strlen(str2);
    
    returned = malloc(sizeof(char) * (len_str1 + len_str2 + 1));
    if (!returned) return NULL;
    for (int i = 0; i < len_str1; i++)
        returned[i] = str1[i];
    for (int i = 0; i < len_str2; i++)
        returned[len_str1 + i] = str2[i];
    returned[len_str1 + len_str2] = '\0';
    return (returned);
}