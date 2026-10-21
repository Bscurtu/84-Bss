
#include "mls.h"

int compare_names(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

char **quick_order(mls_options *opt, int total_files)
{
    struct dirent *stdr;
    char **names;
    int i = 0;

    names = (char **)malloc(sizeof(char *) * (total_files + 3));
    if (!names)
        return (NULL);
    closedir(opt->dr);
    open_dir(opt);
    while ((stdr = readdir(opt->dr)) != NULL)
    {
        names[i] = strdup(stdr->d_name);
        if (!names[i])
            break;
        i++;
    }
    names[i] = NULL;
    closedir(opt->dr);
    open_dir(opt);
    qsort(names, i, sizeof(char *), compare_names);
    return (names);
}