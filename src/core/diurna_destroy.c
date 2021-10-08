#include <stdlib.h>
#include "diurna.h"
#include "diurna_internal.h"

void diurna_destroy(void) {
    if (gl_diurna_ctx_handle != NULL) {
        // Wait log consumer finish consuming remaining messages
        while (gl_diurna_ctx_handle->msg_queue->oldest != NULL) {
            nanosleep((const struct timespec[]) {{0, 50000000}}, NULL);
        }

        // Stop log consumer
        s_diurna_queue *queue = gl_diurna_ctx_handle->msg_queue;
        gl_diurna_ctx_handle->msg_queue = NULL;

#if defined USE_WINTHREAD
        WaitForSingleObject(gl_diurna_ctx_handle->log_consumer_thread, INFINITE);
#else
        pthread_cancel(gl_diurna_ctx_handle->log_consumer_thread);
        pthread_join(gl_diurna_ctx_handle->log_consumer_thread, NULL);
#endif

        // Destroy message queue
        diurna_queue_destroy(queue);

        // Free global context
        free(gl_diurna_ctx_handle->app_name);
        free(gl_diurna_ctx_handle);

        gl_diurna_ctx_handle = NULL;
    }
}
