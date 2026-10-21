
#include "mls.h"

int put_padded(const char *s, int width, int right_align)
{
    int len = 0;

    if (!s)
        s = "";
    while (s[len])
        len++;

    if (right_align)
    {
        while (width > len)
        {
            write(1, " ", 1);
            width--;
        }
        write(1, s, len);
    }
    else
    {
        write(1, s, len);
        while (width > len)
        {
            write(1, " ", 1);
            width--;
        }
    }
    return (0);
}

int output_files(mls_options *opt)
{
    struct stat buf;
    char *tmp;
    char *concat;
    dr_data info;
    char **names;
    int i;
    struct passwd *pw;
    struct group  *gr;
    time_t now = time(NULL);
    time_t six_months = 31556952 / 2;
    char buffer[256];
    char mode_str[11];
    char link_target[1024];
    ssize_t link_len;

    if (!opt || !opt->dr)
        return (1);
    extract_data(opt, &info);
    if (open_dir(opt) == 1)
        return (1);
    names = quick_order(opt, info.total_files);
    if (!names)
        return (1);

    if (opt->l_option == 1)
    {
        snprintf(buffer, sizeof(buffer), "%lld", info.total_blocks);
        put_padded("total ", 0, 0);
        put_padded(buffer, 0, 0);
        put_padded("\n", 0, 0);
    }
    for (i = 0; names[i] != NULL; i++)
    {
        if (opt->a_option == 0 && names[i][0] == '.')
            continue ;

        if (opt->l_option == 1)
        {
            tmp = ef_concat(opt->path, "/");
            if (tmp != NULL)
            {
                concat = ef_concat(tmp, names[i]);
                free(tmp);
            }
            else
                continue ;

            if (lstat(concat, &buf) == -1) {
                error_handler(errno);
                if (concat)
                    free(concat);
                continue ;
            }

            /* 1. PERMITS */
            if (S_ISDIR(buf.st_mode))       mode_str[0] = 'd';
            else if (S_ISLNK(buf.st_mode))  mode_str[0] = 'l';
            else if (S_ISCHR(buf.st_mode))  mode_str[0] = 'c';
            else if (S_ISBLK(buf.st_mode))  mode_str[0] = 'b';
            else if (S_ISSOCK(buf.st_mode)) mode_str[0] = 's';
            else if (S_ISFIFO(buf.st_mode)) mode_str[0] = 'p';
            else                            mode_str[0] = '-';

            mode_str[1] = (buf.st_mode & S_IRUSR) ? 'r' : '-';
            mode_str[2] = (buf.st_mode & S_IWUSR) ? 'w' : '-';
            if (buf.st_mode & S_ISUID && !(buf.st_mode & S_IXUSR))
                mode_str[3] = 'S';
            else if (buf.st_mode & S_ISUID)
                mode_str[3] = 's';
            else if (buf.st_mode & S_IXUSR)
                mode_str[3] = 'x';
            else
                mode_str[3] = '-';
            
            mode_str[4] = (buf.st_mode & S_IRGRP) ? 'r' : '-';
            mode_str[5] = (buf.st_mode & S_IWGRP) ? 'w' : '-';
            if (buf.st_mode & S_ISGID && !(buf.st_mode & S_IXGRP))
                mode_str[6] = 'S';
            else if (buf.st_mode & S_ISGID)
                mode_str[6] = 's';
            else if (buf.st_mode & S_IXGRP)
                mode_str[6] = 'x';
            else
                mode_str[6] = '-';

            mode_str[7] = (buf.st_mode & S_IROTH) ? 'r' : '-';
            mode_str[8] = (buf.st_mode & S_IWOTH) ? 'w' : '-';
            if (buf.st_mode & S_ISVTX && !(buf.st_mode & S_IXOTH))
                mode_str[9] = 'T';
            else if (buf.st_mode & S_ISVTX)
                mode_str[9] = 't';
            else if (buf.st_mode & S_IXOTH)
                mode_str[9] = 'x';
            else
                mode_str[9] = '-';

            mode_str[10] = '\0';

            put_padded(mode_str, 10, 0);
            put_padded(" ", 0, 0);

            /* 2. LINKS */
            snprintf(buffer, sizeof(buffer), "%llu", (unsigned long long)buf.st_nlink);
            put_padded(buffer, info.w_nlink, 1);
            put_padded(" ", 0, 0);

            /* 3. OWNER */
            pw = getpwuid(buf.st_uid);
            if (pw != NULL)
                snprintf(buffer, sizeof(buffer), "%s", pw->pw_name);
            else
                snprintf(buffer, sizeof(buffer), "%u", buf.st_uid);
            put_padded(buffer, info.w_user, 0);
            put_padded(" ", 0, 0);

            /* 4. GROUP */
            gr = getgrgid(buf.st_gid);
            if (gr != NULL)
                snprintf(buffer, sizeof(buffer), "%s", gr->gr_name);
            else
                snprintf(buffer, sizeof(buffer), "%u", buf.st_gid);
            put_padded(buffer, info.w_group, 0);
            put_padded(" ", 0, 0);

            /* 5. SIZE */
            snprintf(buffer, sizeof(buffer), "%lld", (long long)buf.st_size);
            put_padded(buffer, info.w_size > 0 ? info.w_size : (int)info.lg_size, 1);
            put_padded(" ", 0, 0);

            /* 6. DATE */
            if (buf.st_mtime > now || now - buf.st_mtime > six_months)
            {
                strftime(buffer, sizeof(buffer), "%b %e  %Y", localtime(&buf.st_mtime));
                put_padded(buffer, 12, 0);
                put_padded(" ", 0, 0);
            }
            else
            {
                strftime(buffer, sizeof(buffer), "%b %e %H:%M", localtime(&buf.st_mtime));
                put_padded(buffer, 12, 0);
                put_padded(" ", 0, 0);
            }

            /* 7. NAME */
            put_padded(names[i], 0, 0);
            if (S_ISLNK(buf.st_mode))
            {
                link_len = readlink(concat, link_target, sizeof(link_target) - 1);
                if (link_len != -1)
                {
                    link_target[link_len] = '\0';
                    put_padded(" -> ", 0, 0);
                    put_padded(link_target, 0, 0);
                }
            }
            put_padded("\n", 0, 0);
            if (concat)
                free(concat);
        }
        else
        {
            put_padded(names[i], 0, 0);
            put_padded("\n", 0, 0);
        }
    }
    for (i = 0; names[i] != NULL; i++)
        free(names[i]);
    free(names);
    return (0);
}