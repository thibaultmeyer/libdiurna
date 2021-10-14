#ifndef LIBDIURNA_H
# define LIBDIURNA_H

# include <sys/time.h>

# ifdef __cplusplus
extern "C"
{
# endif

# define DIURNA_SUCCESS          0
# define DIURNA_E_NOINIT         1
# define DIURNA_E_NOMEMORY       2
# define DIURNA_E_THREADCREATION 3
# define DIURNA_E_NOMOREAPPENDER 4

/**
 * The different levels of log message.
 */
typedef enum e_diurna_log_level {
    DIURNA_LOGLEVEL_DEBUG = 0,
    DIURNA_LOGLEVEL_INFO  = 1,
    DIURNA_LOGLEVEL_WARN  = 2,
    DIURNA_LOGLEVEL_ERROR = 3
} e_diurna_log_level;

/**
 * Type - Function Appender - All appender must be compliant with this definition
 */
typedef void (*f_appender)(const char *app_name,
                           const enum e_diurna_log_level,
                           const struct timeval *const tv,
                           const char *log_msg);

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

/**
 * Initializes Diurna with the default appender (console).
 *
 * @param app_name The application name
 * @param log_level The log level
 * @return zero in case of success
 */
int diurna_initialize(const char *app_name, enum e_diurna_log_level log_level);

/**
 * Initializes Diurna with a specific appender.
 *
 * @param app_name The application name
 * @param log_level The log level
 * @param appender The appender function
 * @return zero in case of success
 */
int diurna_initialize_ex(const char *app_name, enum e_diurna_log_level log_level, f_appender appender);

/**
 * Destroys Diurna.
 *
 * @return zero in case of success
 */
int diurna_destroy(void);

/**
 * Registers a new appender
 *
 * @param appender The new appender function to register
 * @return zero in case of success
 */
int diurna_cfg_appender_register(f_appender appender);

/**
 * Unregisters all registered appender.
 *
 * @return zero in case of success
 */
int diurna_cfg_appender_unregister_all(void);

/**
 * Defines a new log level.
 *
 * @param log_level The new log level
 * @return zero in case of success
 */
int diurna_cfg_loglevel_set(enum e_diurna_log_level log_level);

/**
 * Returns the Diurna library version as a number.
 *
 * @return The Diurna library version as a number (ie: 1000000 = 1.0.0)
 */
int diurna_version_as_int(void);

/**
 * Returns the Diurna library version as a string.
 *
 * @return The Diurna library version as a string (ie: 1.0.0)
 */
const char *diurna_version_as_str(void);

/**
 * Log a DEBUG message.
 *
 * @param message The message format
 * @param ... The message arguments
 */
void diurna_debug(const char *msg_format, ...);

/**
 * Log an INFORMATION message.
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
 * Log an ERROR message.
 *
 * @param message The message format
 * @param ... The message arguments
 */
void diurna_error(const char *msg_format, ...);

# ifdef __cplusplus
}
# endif

#endif //LIBDIURNA_H
