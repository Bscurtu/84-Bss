
#include "mls.h"

int open_dir(mls_options *opt)
{
    if (!opt)
        return (1);
    if (opt->path != NULL)
        opt->dr = opendir(opt->path);
    else
        opt->dr = opendir(".");
    if (!opt->dr)
        return (error_handler(errno));
    return (0);
}

int error_handler(int error)
{
    char *str;

    str = strerror(error);
    write(2, "mls:", 4);
    if (str)
        while (*str)
        {
            write(2, str, 1);
            str++;
        }
    write(2, "\n", 1);
    return (1);
}