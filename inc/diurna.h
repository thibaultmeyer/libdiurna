#ifndef LIBDIURNA_H
# define LIBDIURNA_H

# include <sys/time.h>

# ifdef __cplusplus
extern "C"
{
# endif

/**
 * All available log levels.
 */
typedef enum e_diurna_log_level {
    DIURNA_LOGLEVEL_DEBUG = 0,
    DIURNA_LOGLEVEL_INFO  = 1,
    DIURNA_LOGLEVEL_WARN  = 2,
    DIURNA_LOGLEVEL_ERROR = 3
} e_diurna_log_level;

typedef void (*f_appender)(const char *app_name,
                           const enum e_diurna_log_level,
                           const struct timeval *const tv,
                           const char *log_msg);

/**
 * Initialize Diurna.
 *
 * @param app_name The application name
 * @param log_level The log level
 * @param appender The appender to use, if NULL, all messages are print on the console
 * @return zero in case of success
 */
int diurna_initialize(const char *app_name, enum e_diurna_log_level log_level, f_appender appender);

/**
 * Destroy Diurna.
 */
void diurna_destroy(void);

/**
 * Log a DEBUG message.
 *
 * @param message The message format
 * @param ... The message arguments
 */
void diurna_debug(const char *msg_format, ...);

/**
 * Log a INFORMATION message.
 *
 * @param message The message format
 * @param ... The message arguments
 */
void diurna_info(const char *msg_format, ...);

/**
 * Log a WARNING message.
 *
 * @param message The message format
 * @param ... The message arguments
 */
void diurna_warn(const char *msg_format, ...);

/**
 * Log a ERROR message.
 *
 * @param message The message format
 * @param ... The message arguments
 */
void diurna_error(const char *msg_format, ...);

/**
 * Returns the Diurna library version as a number.
 *
 * @return The Diurna library version as a number (ie: 1000000 = 1.0.0)
 */
int diurna_get_version_as_int(void);

/**
 * Returns the Diurna library version as a string.
 *
 * @return The Diurna library version as a string (ie: 1.0.0)
 */
const char *diurna_get_version_as_str(void);

/**
 * Appender - Console.
 *
 * @param app_name The application name
 * @param log_level The log level (ie : DIURNA_LOGLEVEL_INFO)
 * @param tv The current time
 * @param log_msg The current message
 */
void diurna_appender_console(const char *app_name,
                             enum e_diurna_log_level log_level,
                             const struct timeval *tv,
                             const char *log_msg);

/**
 * Appender - Syslog.
 *
 * @param app_name The application name
 * @param log_level The log level (ie : DIURNA_LOGLEVEL_INFO)
 * @param tv The current time
 * @param log_msg The current message
 */
void diurna_appender_syslog(const char *app_name,
                            enum e_diurna_log_level log_level,
                            const struct timeval *tv,
                            const char *log_msg);

# ifdef __cplusplus
}
# endif

#endif //LIBDIURNA_H
