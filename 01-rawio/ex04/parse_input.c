
#include "mls.h"

int parse_inputs(mls_options *opt, int ac, char **av, char *this)
{
    if (!opt || !av || ac < 0)
        return (1);
    opt->a_option = FALSE;
    opt->l_option = FALSE;
    opt->path = NULL;
    opt->path_malloc = FALSE;

    for (int i = 1; i < ac; i++)
    {
        if (av[i] == NULL)
            continue ;
        else if (ef_contains(av[i], 'a') == 1 && ef_contains(av[i], 'l') == 1 && ef_contains (av[i], '-') == 1)
        {
            opt->a_option = TRUE;
            opt->l_option = TRUE;
        }
        else if (ef_contains(av[i], 'a') == 1 && ef_contains (av[i], '-') == 1)
            opt->a_option = TRUE;
        else if (ef_contains(av[i], 'l') == 1 && ef_contains (av[i], '-') == 1)
            opt->l_option = TRUE;
        else
            opt->path = av[i];
    }
    if (opt->path == NULL)
        opt->path = this;
    return (0);
}