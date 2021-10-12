#include "diurna.h"
#include "diurna_internal.h"

void diurna_cfg_loglevel_set(enum e_diurna_log_level log_level) {
    if (gl_diurna_ctx_handle != NULL) {
        gl_diurna_ctx_handle->log_level = log_level;
    }
}
