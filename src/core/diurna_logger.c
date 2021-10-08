#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "diurna.h"
#include "diurna_internal.h"

static inline void add_message_to_queue(const enum e_diurna_log_level level,
                                        const char *msg_format,
                                        va_list args) {
    // Prepare log message structure
    struct s_diurna_log_message *log_msg = malloc(sizeof(struct s_diurna_log_message) + 1);
    memset(log_msg, 0, sizeof(struct s_diurna_log_message) + 1);

    // Level
    log_msg->level = level;

    // Message - Retrieve the total size of the message
    va_list args_copy;
    va_copy(args_copy, args);
    size_t msg_formatted_size = vsnprintf(NULL, 0, msg_format, args_copy);
    va_end(args_copy);

    // Message - Create message
    log_msg->message = malloc(sizeof(char) * msg_formatted_size + 1);
    vsnprintf(log_msg->message, msg_formatted_size + 1, msg_format, args);

    // Time
    gettimeofday(&log_msg->time, NULL);

    // Append to the queue
    diurna_queue_queue(gl_diurna_ctx_handle->msg_queue, log_msg);
}

void diurna_debug(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_DEBUG) {
        va_list args;
        va_start(args, msg_format);
        add_message_to_queue(DIURNA_LOGLEVEL_DEBUG, msg_format, args);
        va_end(args);
    }
}

void diurna_info(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_INFO) {
        va_list args;
        va_start(args, msg_format);
        add_message_to_queue(DIURNA_LOGLEVEL_INFO, msg_format, args);
        va_end(args);
    }
}

void diurna_warn(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_WARN) {
        va_list args;
        va_start(args, msg_format);
        add_message_to_queue(DIURNA_LOGLEVEL_WARN, msg_format, args);
        va_end(args);
    }
}

void diurna_error(const char *msg_format, ...) {
    if (gl_diurna_ctx_handle->log_level <= DIURNA_LOGLEVEL_ERROR) {
        va_list args;
        va_start(args, msg_format);
        add_message_to_queue(DIURNA_LOGLEVEL_ERROR, msg_format, args);
        va_end(args);
    }
}
