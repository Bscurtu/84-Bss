
#include "mls.h"

int main(int ac, char **av)
{
    int returned;
    mls_options opt;
    char this[2];

    returned = 0;
    this[0] = '.';
    this[1] = 0;
    returned = parse_inputs(&opt, ac, av, this);
    if (returned == 0)
        returned = open_dir(&opt);
    if (returned == 0)
        returned = output_files(&opt);
    if (opt.dr)
        closedir(opt.dr);
    if (opt.path_malloc == TRUE)
        free(opt.path);
    return (returned);
}