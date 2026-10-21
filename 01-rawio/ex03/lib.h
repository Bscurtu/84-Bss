#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#ifndef BLOCK
    #define BLOCK 4096
#endif

//Me dan el archivo -> Compruebo si me han dado -n -> Abro el archivo -> Voy al final -> leo y busco los saltos de linea -> lo vuelvo a leer(tamaño max 8192) y lo escribo

/* ################## <OPEN_FILE.C> ################## */

/**
 * @brief Opens the input for mtail: a file, or stdin when no name is given.
 *
 * @param filename Path to open, or NULL / "-" to read from stdin.
 *
 * @return File descriptor ready to read (STDIN_FILENO for stdin),
 *         or -1 on error with errno set by open(2).
 */
int open_input(const char *filename);

/**
 * @brief Reads exactly `quantity` bytes starting at `offset`, unless EOF comes first.
 *
 * Retries on partial reads and EINTR, so a short count only means EOF.
 *
 * @param fd       Seekable file descriptor.
 * @param buf      Destination, at least `quantity` bytes long.
 * @param offset   Absolute position to start reading from.
 * @param quantity Number of bytes to read.
 *
 * @pre  fd is seekable (regular file); buf != NULL.
 * @post The file offset of fd is left at offset + returned value.
 *
 * @return Bytes read (0..quantity; less than quantity only at EOF),
 *         or -1 on error with errno set.
 */
ssize_t read_at(int fd, char *buf, off_t offset, size_t quantity);




/* ################## <LINE_COUNT.C> ################## */

/**
 * @brief Checks if the -n parameter is used, and sets the number of lines to retrieve.
 *
 * @param av The vector of all parameters.
 * @param ac The quantity of all parameters.
 *
 * @post if -n is used
 *
 * @return The number of lines to retreive, 0 if number of lines is 0, and the program won't print anything.
 *         If the number is negative it will be used a positive (like real tail command).
 *         -1 Under any error.
 */
ssize_t line_number(int ac, char **av, ssize_t *n_lines);



/* ################## <EXTRAS.C> ################## */
/**
 * @brief Compares two strings and returns the difference.
 *
 * The strings must be NULL terminated or the outcome will be undefined.
 *
 * @param str1  First string to compare
 * @param str2  Second string to compare
 *
 * @pre  str1 != NULL;
 * @pre  str2 != NULL;
 *
 * @return returns the difference between the ascii value of the first difference (like strcmp).
 */
int ef_strcmp(const char *str1, const char *str2);

/**
 * @brief Extracts a number from a string, the number will always be positive.
 *
 * The string must be NULL terminated or the outcome will be undefined.
 *
 * @param str  String to get to number
 *
 * @pre  str != NULL;
 *
 * @return a positive number extracted from the string.
 *         -1 if the input was not valid.
 */
long ef_extract_number(const char *str);

long ef_strlen(char *str);

/* ################## <ARGS.C> ################## */

/**
 * @brief Parses the command line: optional "-n NUM" and the file name.
 *
 * @param ac, av     As received by main.
 * @param n_lines    Out: number of lines to print (10 if -n is absent).
 * @param file_index Out: index in av of the first file name (== ac if none).
 *
 * @return 0 on success, -1 if the arguments are invalid (error already printed).
 */
int parse_args(int ac, char **av, ssize_t *n_lines, int *file_index);



/* ################## <READER.C> ################## */
/**
 * @brief Reads exactly `quantity` bytes starting at `offset`, unless EOF comes first.
 *
 * Retries on partial reads and EINTR, so a short count only means EOF.
 *
 * @pre  fd is seekable (regular file); buf != NULL.
 * @post The file offset of fd is left at offset + returned value.
 *
 * @return Bytes read (0..quantity; less than quantity only at EOF),
 *         or -1 on error with errno set.
 */
off_t read_file(int fd, int n_lines);


/* ################## Print_file.c ################## */
/**
 * @brief Printf from a offset to the final of the file
 * Retries on partial writes until reaches final.
 *
 * @param fd, file descriptor to read from
 * @param offset, point where to start reading
 *
 * @pre  fd is >= 0;
 *
 * @return 0 if everything worked properly.
 *         -1 Under any error and errno will be changed.
 */
int print_lines(int fd, off_t offset);

/* ################## pipe.c ################## */
/**
 * @brief Printf from a offset to the final of the file
 * Retries on partial writes until reaches final.
 *
 * @param fd, file descriptor to read from
 * @param offset, point where to start reading
 *
 * @pre  fd is >= 0;
 *
 * @return 0 if everything worked properly.
 *         -1 Under any error and errno will be changed.
 */
int print_lines(int fd, off_t offset);


void process_stream_input(int fd, int n_lines);