#include "diurna.h"
#include "diurna_internal.h"

int diurna_cfg_appender_unregister_all(void) {
    if (gl_diurna_ctx_handle != NULL) {
        for (int idx = 0; idx < DIURNA_MAX_APPENDER; ++idx) {
            gl_diurna_ctx_handle->appender[idx] = NULL;
        }

        return (DIURNA_SUCCESS);
    }

    return (DIURNA_E_NOINIT);
}
