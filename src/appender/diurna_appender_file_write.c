#include <stdio.h>
#include <stdlib.h>
#include "diurna_internal.h"

void diurna_appender_file_write(const void *appender_ctx,
                                const char *const app_name,
                                const enum e_diurna_log_level level,
                                const struct timeval *const tv,
                                const char *const log_msg) {
    (void) app_name;     // Unused parameter

    // Convert timeval to human reading time
    char      date_stamp[24] = {0};
    struct tm *tm_stamp      = gmtime(&tv->tv_sec);
    strftime(date_stamp, sizeof(date_stamp), "%Y-%m-%d %H:%M:%S", tm_stamp);

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

    // Write message to the open file
    fprintf((FILE *) appender_ctx, "%s.%.03d [%s] %s\n", date_stamp, (int) (tv->tv_usec / 1000), level_as_str, log_msg);
}
