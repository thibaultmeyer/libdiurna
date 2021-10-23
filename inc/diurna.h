#ifndef LIBDIURNA_H
# define LIBDIURNA_H

#if defined _WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <winsock.h>
# else

#  include <sys/time.h>

# endif


# ifdef __cplusplus
extern "C"
{
# endif

# define DIURNA_SUCCESS           0
# define DIURNA_E_NOINIT          1
# define DIURNA_E_NOMEMORY        2
# define DIURNA_E_THREADCREATION  3
# define DIURNA_E_NOMOREAPPENDER  4
# define DIURNA_E_INVALIDAPPENDER 5

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
 * Type - Appender - Writes a new message.
 */
typedef void (*f_appender_write)(const void *appender_ctx,
                                 const char *app_name,
                                 const enum e_diurna_log_level,
                                 const struct timeval *const tv,
                                 const char *log_msg);

/**
 * Type - Appender - Destroys the appender.
 */
typedef void (*f_appender_destroy)(void *ctx);

/**
 * Represents an Appender context.
 */
typedef struct s_diurna_appender {
    void *ctx;

    f_appender_write   f_write;
    f_appender_destroy f_destroy;
}            s_diurna_appender;

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
 * @param appender_ctx The appender context to use
 * @return zero in case of success
 */
int diurna_initialize_ex(const char *app_name, enum e_diurna_log_level log_level, struct s_diurna_appender *appender);

/**
 * Destroys Diurna.
 *
 * @return zero in case of success
 */
int diurna_destroy(void);

/**
 * Registers a new appender
 *
 * @param appender_ctx The new appender context to register
 * @return zero in case of success
 */
int diurna_cfg_appender_register(struct s_diurna_appender *appender);

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

/**
 * Creates a new "Console" appender.
 *
 * @return Newly created "Console" appender, otherwise, NULL
 */
struct s_diurna_appender *diurna_appender_console_create(void);

# if defined HAVE_SYSLOG

/**
 * Creates a new "Syslog" appender.
 *
 * @return Newly created "Syslog" appender, otherwise, NULL
 */
struct s_diurna_appender *diurna_appender_syslog_create(void);

# endif

# ifdef __cplusplus
}
# endif

#endif //LIBDIURNA_H
