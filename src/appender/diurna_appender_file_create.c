#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diurna_internal.h"

struct s_diurna_appender *diurna_appender_file_create(const char *filename) {
    // Create appender
    struct s_diurna_appender *appender = malloc(sizeof(struct s_diurna_appender) + 1);
    if (appender == NULL) {
        return (NULL);
    }

    memset(appender, 0, sizeof(struct s_diurna_appender) + 1);

    appender->f_write   = &diurna_appender_file_write;
    appender->f_destroy = &diurna_appender_file_destroy;

    // Open file
    appender->ctx = fopen(filename, "a+");
    if (appender->ctx == NULL) {
        free(appender);
        return (NULL);
    }

    return (appender);
}
