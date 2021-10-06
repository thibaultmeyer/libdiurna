#ifndef LIBDIURNA_H
# define LIBDIURNA_H

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

/**
 * Diurna context.
 */
typedef struct s_diurna_context {
    char                    *app_name;
    enum e_diurna_log_level log_level;
} s_diurna_context;

/**
 * Handle to the global Diurna context.
 */
extern s_diurna_context *gl_diurna_ctx_handle;

/**
 * Initialize Diurna.
 *
 * @param app_name The application name
 * @return zero in case of success
 */
int diurna_initialize(const char* app_name);

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
 * @return The Diurna library version as a number (ie: 10000 = 1.0.0)
 */
int diurna_get_version_as_int(void);

/**
 * Returns the Diurna library version as a string.
 *
 * @return The Diurna library version as a string (ie: 1.0.0)
 */
const char *diurna_get_version_as_str(void);

# ifdef __cplusplus
}
# endif

#endif //LIBDIURNA_H
