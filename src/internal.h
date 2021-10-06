#ifndef LIBDIURNA_INTERNAL_H
# define LIBDIURNA_INTERNAL_H

/**
 * Diurna context.
 */
typedef struct s_diurna_context {
    char                    *app_name;
    enum e_diurna_log_level log_level;
    f_appender              appender[32];

} s_diurna_context;

/**
 * Handle to the global Diurna context.
 */
extern s_diurna_context *gl_diurna_ctx_handle;

#endif //LIBDIURNA_INTERNAL_H
