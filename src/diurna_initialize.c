#include <stdlib.h>
#include <string.h>
#include "diurna.h"
#include "internal.h"

s_diurna_context *gl_diurna_ctx_handle = NULL;

int diurna_initialize(const char *const app_name,
                      const enum e_diurna_log_level log_level,
                      const f_appender appender) {
    if (gl_diurna_ctx_handle == NULL) {
        // Allocate memory
        gl_diurna_ctx_handle = malloc(sizeof(struct s_diurna_context));
        memset(gl_diurna_ctx_handle, 0, sizeof(struct s_diurna_context));

        // Initialize context
        gl_diurna_ctx_handle->app_name  = strdup(app_name);
        gl_diurna_ctx_handle->log_level = log_level;
        gl_diurna_ctx_handle->msg_queue = diurna_queue_initialize();
        gl_diurna_ctx_handle->appender[0] = appender == NULL
                                            ? &diurna_appender_console
                                            : appender;

        // Create "Appender" Thread
#if defined USE_WINTHREAD
        gl_diurna_ctx_handle->log_consumer_thread = CreateThread(NULL, 0, &log_consumer_thread, NULL, 0, NULL);
#else
        pthread_create(&gl_diurna_ctx_handle->log_consumer_thread, 0, &log_consumer_thread, NULL);
#endif
    }

    return (0);
}
