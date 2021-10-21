#include <stdlib.h>
#include "diurna.h"
#include "diurna_internal.h"

int diurna_cfg_appender_unregister_all(void) {
    if (gl_diurna_ctx_handle == NULL) {
        return (DIURNA_E_NOINIT);
    }

    for (int idx = 0; idx < DIURNA_MAX_APPENDER; ++idx) {
        if (gl_diurna_ctx_handle->appender[idx] != NULL) {
            if (gl_diurna_ctx_handle->appender[idx]->f_destroy != NULL) {
                gl_diurna_ctx_handle->appender[idx]->f_destroy(gl_diurna_ctx_handle->appender[idx]->ctx);
            }

            free(gl_diurna_ctx_handle->appender[idx]);
            gl_diurna_ctx_handle->appender[idx] = NULL;
        }
    }

    return (DIURNA_SUCCESS);
}
