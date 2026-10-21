
#include "lib.h"

typedef struct {
    char **lines;
    int max_lines;
    int current_index;
    int total_read;
} circular_buffer;

circular_buffer* init_buffer(int n_lines)
{
    circular_buffer *cb = (circular_buffer *)malloc(sizeof(circular_buffer));
    if (!cb) return NULL;
    
    cb->lines = (char **)malloc(sizeof(char *) * n_lines);
    if (!cb->lines) {
        free(cb);
        return NULL;
    }
    for (int i = 0; i < n_lines; i++) {
        cb->lines[i] = NULL;
    }
    
    cb->max_lines = n_lines;
    cb->current_index = 0;
    cb->total_read = 0;
    
    return (cb);
}

void buffer_add_line(circular_buffer *cb, char *line)
{
    if (cb->max_lines == 0)
    {
        free(line);
        return;
    }
    if (cb->total_read >= cb->max_lines)
        free(cb->lines[cb->current_index]);

    cb->lines[cb->current_index] = line;
    cb->current_index = (cb->current_index + 1) % cb->max_lines;
    cb->total_read++;
}

void print_buffer(circular_buffer *cb)
{
    if (cb->max_lines == 0 || cb->total_read == 0)
        return;
    int start_index = 0;
    int lines_to_print = cb->total_read;
    if (cb->total_read >= cb->max_lines)
    {
        start_index = cb->current_index;
        lines_to_print = cb->max_lines;
    }
    for (int i = 0; i < lines_to_print; i++)
    {
        int index = (start_index + i) % cb->max_lines;
        if (cb->lines[index])
            write(1, cb->lines[index], ef_strlen(cb->lines[index]));
    }
}

void free_buffer(circular_buffer *cb)
{
    int limit;
    if (!cb)
        return;

    if (cb->total_read < cb->max_lines)
        limit = cb->total_read;
    else
        limit = cb->max_lines;
    
    for (int i = 0; i < limit; i++)
    {
        if (cb->lines[i])
            free(cb->lines[i]);
    }
    free(cb->lines);
    free(cb);
}

char *append_char(char *str, int *len, char c) {
    char *new_str = (char *)malloc(*len + 2);
    if (!new_str) return NULL;
    
    if (str) {
        for (int i = 0; i < *len; i++) {
            new_str[i] = str[i];
        }
        free(str);
    }
    
    new_str[*len] = c;
    new_str[*len + 1] = '\0';
    (*len)++;
    
    return new_str;
}

void process_stream_input(int fd, int n_lines) {
    circular_buffer *cb = init_buffer(n_lines);
    if (!cb)
        return;

    char buffer[BLOCK];
    int bytes_read;
    char *current_line = NULL;
    int line_len = 0;

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0)
    {
        for (int i = 0; i < bytes_read; i++)
        {
            current_line = append_char(current_line, &line_len, buffer[i]);
            if (buffer[i] == '\n')
            {
                buffer_add_line(cb, current_line);
                current_line = NULL;
                line_len = 0;
            }
        }
    }
    if (current_line != NULL && line_len > 0) {
        buffer_add_line(cb, current_line);
    }
    print_buffer(cb);
    free_buffer(cb);
}