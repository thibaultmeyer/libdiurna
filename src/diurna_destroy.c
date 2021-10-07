#include <stdlib.h>
#include "diurna.h"
#include "internal.h"

void diurna_destroy(void) {
    if (gl_diurna_ctx_handle != NULL) {
        while (gl_diurna_ctx_handle->msg_queue->oldest != NULL) {
            nanosleep((const struct timespec[]) {{0, 50000000}}, NULL);
        }

        diurna_queue_destroy(gl_diurna_ctx_handle->msg_queue);
        free(gl_diurna_ctx_handle->app_name);
        free(gl_diurna_ctx_handle);

        gl_diurna_ctx_handle = NULL;
    }
}
