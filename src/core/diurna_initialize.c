#include <stdlib.h>
#include <string.h>
#include "diurna.h"
#include "diurna_internal.h"

s_diurna_context *gl_diurna_ctx_handle = NULL;

int diurna_initialize(const char *const app_name, const enum e_diurna_log_level log_level) {
    if (gl_diurna_ctx_handle == NULL) {
        // Allocate memory
        gl_diurna_ctx_handle = malloc(sizeof(struct s_diurna_context) + 1);
        if (gl_diurna_ctx_handle == NULL) {
            return (DIURNA_E_NOMEMORY);
        }
        memset(gl_diurna_ctx_handle, 0, sizeof(struct s_diurna_context) + 1);

        // Initialize context
        gl_diurna_ctx_handle->app_name  = strdup(app_name);
        gl_diurna_ctx_handle->log_level = log_level;

        gl_diurna_ctx_handle->msg_queue = diurna_queue_initialize();
        if (gl_diurna_ctx_handle->msg_queue == NULL) {
            free(gl_diurna_ctx_handle);
            return (DIURNA_E_NOMEMORY);
        }

        gl_diurna_ctx_handle->appender[0] = diurna_appender_console_create();
        if (gl_diurna_ctx_handle->appender[0] == NULL) {
            free(gl_diurna_ctx_handle->msg_queue);
            free(gl_diurna_ctx_handle);
            return (DIURNA_E_NOMEMORY);
        }

        // Create "Appender" Thread
#if defined USE_WINTHREAD
        gl_diurna_ctx_handle->log_consumer_thread = CreateThread(NULL, 0, &log_consumer_thread, NULL, 0, NULL);
        if (gl_diurna_ctx_handle->log_consumer_thread == NULL) {
#else
        int ret = pthread_create(&gl_diurna_ctx_handle->log_consumer_thread, NULL, &log_consumer_thread, NULL);
        if (ret != 0) {
#endif
            diurna_queue_destroy(gl_diurna_ctx_handle->msg_queue);
            free(gl_diurna_ctx_handle);
            return (DIURNA_E_THREADCREATION);
        }
    }

    return (DIURNA_SUCCESS);
}
