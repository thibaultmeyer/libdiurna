#include <stdlib.h>
#include <string.h>
#include "diurna.h"
#include "internal.h"

s_diurna_context *gl_diurna_ctx_handle = NULL;

int diurna_initialize(const char *const app_name,
                      const enum e_diurna_log_level log_level,
                      const f_appender appender) {
    if (gl_diurna_ctx_handle == NULL) {
        gl_diurna_ctx_handle = malloc(sizeof(struct s_diurna_context));
        gl_diurna_ctx_handle->app_name  = strdup(app_name);
        gl_diurna_ctx_handle->log_level = log_level;
        gl_diurna_ctx_handle->appender[0] = appender == NULL
                ? &diurna_appender_console
                : appender;
    }

    return (0);
}
