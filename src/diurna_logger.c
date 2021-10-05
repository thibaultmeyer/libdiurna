#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "diurna.h"

static inline void internal_logger(const enum e_diurna_log_level level,
                                   const char *msg_format,
                                   va_list args) {
    // Retrieve the total size of the message
    va_list args_copy;
    va_copy(args_copy, args);
    size_t msg_size = snprintf(NULL, 0, msg_format, args_copy);
    va_end(args_copy);

    // Create message
    char *msg = malloc(sizeof(char) * msg_size + 1);
    vsnprintf(msg, msg_size + 1, msg_format, args);

    // Level
    char *level_as_str;
    switch (level) {
        case DIURNA_LOGLEVEL_DEBUG:
            level_as_str = "DEBUG";
            break;
        case DIURNA_LOGLEVEL_INFO:
            level_as_str = "INFO";
            break;
        case DIURNA_LOGLEVEL_WARN:
            level_as_str = "WARN";
            break;
        case DIURNA_LOGLEVEL_ERROR:
            level_as_str = "ERROR";
            break;
        default:
            level_as_str = "NONE";
    }

    // Output message to all configured logger output
    printf("2021-01-01 12:32:23.324 [%s] %s\n", level_as_str, msg);
    free(msg);
}

void diurna_debug(const char *msg_format, ...) {
    va_list args;
    va_start(args, msg_format);
    internal_logger(DIURNA_LOGLEVEL_DEBUG, msg_format, args);
    va_end(args);
}

void diurna_info(const char *msg_format, ...) {
    va_list args;
    va_start(args, msg_format);
    internal_logger(DIURNA_LOGLEVEL_INFO, msg_format, args);
    va_end(args);
}

void diurna_warn(const char *msg_format, ...) {
    va_list args;
    va_start(args, msg_format);
    internal_logger(DIURNA_LOGLEVEL_WARN, msg_format, args);
    va_end(args);
}

void diurna_error(const char *msg_format, ...) {
    va_list args;
    va_start(args, msg_format);
    internal_logger(DIURNA_LOGLEVEL_ERROR, msg_format, args);
    va_end(args);
}
