#include <syslog.h>
#include "diurna.h"

void diurna_appender_syslog(const char *const app_name,
                            const enum e_diurna_log_level level,
                            const struct timeval *const tv,
                            const char *const log_msg) {
    (void) tv; // Unused parameter

    // Open syslog connection
    openlog(app_name, LOG_PID | LOG_CONS, LOG_USER);

    // Level
    int level_syslog;
    switch (level) {
        case DIURNA_LOGLEVEL_DEBUG:
            level_syslog = LOG_DEBUG;
            break;
        case DIURNA_LOGLEVEL_INFO:
            level_syslog = LOG_INFO;
            break;
        case DIURNA_LOGLEVEL_WARN:
            level_syslog = LOG_WARNING;
            break;
        case DIURNA_LOGLEVEL_ERROR:
            level_syslog = LOG_ERR;
            break;
        default:
            level_syslog = LOG_INFO;
    }

    // Log
    syslog(level_syslog, "%s", log_msg);

    // Close syslog connection
    closelog();
}
