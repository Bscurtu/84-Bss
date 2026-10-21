#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>
#include <grp.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#define TRUE 1
#define FALSE 0

typedef struct
{
    char *path;
    bool path_malloc;
    bool a_option;
    bool l_option;
    DIR *dr;
} mls_options;

typedef struct
{
    unsigned int lg_size;
    unsigned int lg_name;
    long long total_size;
    unsigned int total_files;
    long long total_blocks;

    int w_nlink;
    int w_user;
    int w_group;
    int w_size;
} dr_data;

/* ################## <parse_input.c> ################## */
/**
 * @brief Checks the input for "-l", "-a" and the path. Only one path can be displayed at a time.
 *
 * Only the last path will be displayed
 *
 * @param opt a struct will all the options.
 * @param ac quantity of inputs.
 * @param av vector with all the inputs.
 *
 * @return 0 if everything if everything worked properly
 *         1 under any error.
 *
 */
int parse_inputs(mls_options *opt, int ac, char **av, char *this);


/* ################## <open_dir.c> ################## */
/**
 * @brief Opens the directory specified in "path".
 *
 * Handles error with errno and checks whether path is a file or does not exist.
 *
 * @param opt a struct will all the options.
 *
 * @pre opt is not NULL
 *
 * @return 0 if everything if everything worked properly
 *         1 under any error, and errno will be changed.
 *
 */
int open_dir(mls_options *opt);

/**
 * @brief Outputs the error in open_dir function.
 *
 * Handles error with errno and checks whether path is a file or does not exist.
 *
 * @param error the error.
 *
 * @return allways 1 as an error occured
 *
 */
int error_handler(int error);

/* ################## <output_files.c> ################## */
/**
 * @brief reads and write all files in the specified path, it checks for "-l" or "-a" style.
 *
 * @param opt a struct will all the options.
 *
 * @pre opt is not NULL.
 * @pre opt->dr is not NULL.
 *
 * @return 0 if everything if everything worked properly
 *         1 under any error, and errno will be changed.
 *
 */
int output_files(mls_options *opt);

/* ################## <bubble_sort.c> ################## */
/**
 * @brief creates an array of chars * and orders the name of the files.
 *
 * @param dr the directory.
 * @param total_files the number of files in the directory.
 *
 * @pre dr is not NULL;
 * @pre total_files > 0
 *
 * @return the array of chars *.
 *
 */
char **quick_order(mls_options *opt, int total_files);


void extract_data(mls_options *opt, dr_data *info);

char *ef_concat(char *str1, char *str2);

int ef_contains(const char *str1, char str2);