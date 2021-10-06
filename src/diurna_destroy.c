#include <stdlib.h>
#include "diurna.h"
#include "internal.h"

void diurna_destroy(void) {
    if (gl_diurna_ctx_handle != NULL) {
        free(gl_diurna_ctx_handle->app_name);
        free(gl_diurna_ctx_handle);

        gl_diurna_ctx_handle = NULL;
    }
}
