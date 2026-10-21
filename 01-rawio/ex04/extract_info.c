
#include "mls.h"

static int get_num_len(long long num)
{
    int len = 1;
    while (num > 9)
    {
        num /= 10;
        len++;
    }
    return (len);
}

void extract_data(mls_options *opt, dr_data *info)
{
    struct dirent *stdr;
    struct stat buf;
    unsigned int len;
    char *tmp;
    char *concat;
    struct passwd *pw;
    struct group *gr;
    int temp_len;

    info->lg_size = 0;
    info->lg_name = 0;
    info->total_files = 0;
    info->total_size = 0;
    info->total_blocks = 0;
    info->w_nlink = 0;
    info->w_user = 0;
    info->w_group = 0;
    info->w_size = 0;

    while ((stdr = readdir(opt->dr)) != NULL)
    {
        if (opt->a_option == FALSE && stdr->d_name[0] == '.')
        {
            info->total_files++;
            continue ;
        }
        tmp = ef_concat(opt->path, "/");
        if (tmp)
        {
            concat = ef_concat(tmp, stdr->d_name);
            free(tmp);
        }
        else
            continue ;
        info->total_files++;
        len = strlen(stdr->d_name);
        if (len > info->lg_name)
            info->lg_name = len;
        if (lstat(concat, &buf) == 0)
        {
            if (buf.st_size > info->lg_size)
                info->lg_size = buf.st_size;
            temp_len = get_num_len((long long)buf.st_nlink);
            if (temp_len > info->w_nlink)
                info->w_nlink = temp_len;
            pw = getpwuid(buf.st_uid);
            if (pw != NULL)
                temp_len = strlen(pw->pw_name);
            else
                temp_len = get_num_len((long long)buf.st_uid);
            
            if (temp_len > info->w_user)
                info->w_user = temp_len;
            gr = getgrgid(buf.st_gid);
            if (gr != NULL)
                temp_len = strlen(gr->gr_name);
            else
                temp_len = get_num_len((long long)buf.st_gid);
            
            if (temp_len > info->w_group)
                info->w_group = temp_len;
            temp_len = get_num_len((long long)buf.st_size);
            if (temp_len > info->w_size)
                info->w_size = temp_len;

            info->total_blocks += buf.st_blocks;
        }
        if (concat)
            free(concat);
    }
    
    if (info->total_blocks % 2 != 0)
        info->total_blocks++;
    info->total_blocks /= 2;
    
    closedir(opt->dr);
}