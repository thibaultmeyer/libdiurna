#include <stdlib.h>
#include "diurna.h"

void diurna_destroy(void) {
    free(gl_diurna_ctx_handle);
    gl_diurna_ctx_handle = NULL;
}
