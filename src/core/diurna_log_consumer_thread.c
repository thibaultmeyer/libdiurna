#include <stdlib.h>
#include "diurna.h"
#include "diurna_internal.h"

void *log_consumer_thread(void *arg) {
    (void) arg; // Unused parameter

    struct s_diurna_log_message *msg;
    while (gl_diurna_ctx_handle->msg_queue != NULL) {
        msg = diurna_queue_dequeue(gl_diurna_ctx_handle->msg_queue);

        if (msg != NULL) {
            for (int idx = 0; gl_diurna_ctx_handle->appender[idx] != NULL; ++idx) {
                gl_diurna_ctx_handle->appender[idx]->f_write(
                        gl_diurna_ctx_handle->appender[idx]->ctx,
                        gl_diurna_ctx_handle->app_name,
                        msg->level,
                        &msg->time,
                        msg->message);
            }

            free(msg->message);
            free(msg);
        } else {
            // No message on the queue, wait 50 ms
#if defined WIN32
            nanosleep(50000000);
#else
            nanosleep((const struct timespec[]) {{0, 50000000}}, NULL);
#endif
        }
    }

#if defined USE_WINTHREAD
    ExitThread(EXIT_SUCCESS);
#else
    pthread_exit(EXIT_SUCCESS);
#endif

    return (NULL);
}
