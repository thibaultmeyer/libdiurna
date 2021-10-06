#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "diurna.h"
#include "internal.h"

static inline void internal_logger(const enum e_diurna_log_level level,
                                   const char *msg_format,
                                   va_list args) {
    // Retrieve the total size of the message
    va_list args_copy;
    va_copy(args_copy, args);
    size_t msg_size = vsnprintf(NULL, 0, msg_format, args_copy);
    va_end(args_copy);

    // Create message
    char *msg = malloc(sizeof(char) * msg_size + 1);
    vsnprintf(msg, msg_size + 1, msg_format, args);

    // Time
    struct timeval tv = {0};
    gettimeofday(&tv, NULL);

    for (int idx = 0; gl_diurna_ctx_handle->appender[idx] != NULL; ++idx) {
        gl_diurna_ctx_handle->appender[idx](gl_diurna_ctx_handle->app_name, level, &tv, msg);
    }
    free(msg);
}

void diurna_debug(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_DEBUG) {
        va_list args;
        va_start(args, msg_format);
        internal_logger(DIURNA_LOGLEVEL_DEBUG, msg_format, args);
        va_end(args);
    }
}

void diurna_info(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_INFO) {
        va_list args;
        va_start(args, msg_format);
        internal_logger(DIURNA_LOGLEVEL_INFO, msg_format, args);
        va_end(args);
    }
}

void diurna_warn(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_WARN) {
        va_list args;
        va_start(args, msg_format);
        internal_logger(DIURNA_LOGLEVEL_WARN, msg_format, args);
        va_end(args);
    }
}

void diurna_error(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_ERROR) {
        va_list args;
        va_start(args, msg_format);
        internal_logger(DIURNA_LOGLEVEL_ERROR, msg_format, args);
        va_end(args);
    }
}
