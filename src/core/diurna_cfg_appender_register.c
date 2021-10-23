#include "diurna.h"
#include "diurna_internal.h"

int diurna_cfg_appender_register(struct s_diurna_appender *const appender) {
    if (gl_diurna_ctx_handle != NULL) {
        // Check appender
        if (appender == NULL || appender->f_write == NULL) {
            return (DIURNA_E_INVALIDAPPENDER);
        }

        // Try to register appender
        for (int idx = 0; idx < DIURNA_MAX_APPENDER; ++idx) {
            if (gl_diurna_ctx_handle->appender[idx] == NULL) {
                gl_diurna_ctx_handle->appender[idx] = appender;
                return (DIURNA_SUCCESS);
            }
        }

        return (DIURNA_E_NOMOREAPPENDER);
    }

    return (DIURNA_E_NOINIT);
}
